#!/bin/bash

ORANGE='\033[0;33m'
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

print_header() {
	echo -e "${RED}██╗██████╗ ███████╗    ██████╗ ██╗███████╗ ██████╗ ${BLUE}         ██╗  ██╗██████╗ "
	echo -e "${RED}██║██╔══██╗██╔════╝    ██╔══██╗██║██╔════╝██╔════╝ ${BLUE}         ██║  ██║╚════██╗"
	echo -e "${RED}██║██║  ██║█████╗█████╗██║  ██║██║█████╗  ██║  ███╗${BLUE}         ███████║ █████╔╝"
	echo -e "${RED}██║██║  ██║██╔══╝╚════╝██║  ██║██║██╔══╝  ██║   ██║${BLUE}         ╚════██║██╔═══╝ "
	echo -e "${RED}██║██████╔╝███████╗    ██████╔╝██║███████╗╚██████╔╝${BLUE}              ██║███████╗"
	echo -e "${RED}╚═╝╚═════╝ ╚══════╝    ╚═════╝ ╚═╝╚══════╝ ╚═════╝ ${BLUE}              ╚═╝╚══════╝"
	echo -e "${ORANGE}██╗  ██╗ ██████╗ ██████╗ ███╗   ███╗██╗██████╗ ███████╗██╗   ██╗${GREEN}       ██╗  "
	echo -e "${ORANGE}██║  ██║██╔═══██╗██╔══██╗████╗ ████║██║██╔══██╗██╔════╝██║   ██║${GREEN}   ██╗ ╚═██╗"
	echo -e "${ORANGE}███████║██║   ██║██████╔╝██╔████╔██║██║██║  ██║█████╗  ██║   ██║${GREEN}   ╚═╝   ██║"
	echo -e "${ORANGE}██╔══██║██║   ██║██╔══██╗██║╚██╔╝██║██║██║  ██║██╔══╝  ╚██╗ ██╔╝${GREEN}   ██╗   ██║"
	echo -e "${ORANGE}██║  ██║╚██████╔╝██║  ██║██║ ╚═╝ ██║██║██████╔╝███████╗ ╚████╔╝ ${GREEN}   ╚═╝ ██╔═╝"
	echo -e "${ORANGE}╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═════╝ ╚══════╝  ╚═══╝  ${GREEN}       ╚═╝  ${NC}"
	echo -e "${GREEN} ____  __  ____  ____  _  _ ${RED}    ____  ____  ____  ____  ____  ____  ${NC}"
	echo -e "${GREEN}(  _ \(  )(  _ \(  __)( \/ )${RED}   (_  _)(  __)/ ___)(_  _)(  __)(  _ \ ${NC}"
	echo -e "${GREEN} ) __/ )(  ) __/ ) _)  )  ( ${RED}     )(   ) _) \___ \  )(   ) _)  )   / ${NC}"
	echo -e "${GREEN}(__)  (__)(__)  (____)(_/\_)${RED}    (__) (____)(____/ (__) (____)(__\_) ${NC}"
}


create_infile() {
	echo "TESTER HORMIDEV" > infile
	echo "" >> infile
	echo "test 1 (argumentos invalidos)" >> infile
	echo "test 2 (./pipex noexiste "grep hello" "wc" outfile)" >> infile
}

delete_files() {
	rm -f outfile
	rm -f shelloutfile
	rm -f errorfile
	rm -f shellerrorfile
	rm -f testfile
}

test_1() {
	ok=true

	./pipex > testfile 2>&1
	status=$?
	if [[ status -ne 1 ]]; then
		ok=false
	fi
	first_line=$(head -n 1 testfile)
	if [[ "$first_line" != *"Error"* ]]; then
		ok=false
	fi

	./pipex arg1 arg2 arg3 > testfile 2>&1
	status=$?
	if [[ status -ne 1 ]]; then
		ok=false
	fi
	first_line=$(head -n 1 testfile)
	if [[ "$first_line" != *"Error"* ]]; then
		ok=false
	fi

	./pipex arg1 arg2 arg3 arg4 arg5 > testfile 2>&1
	status=$?
	if [[ status -ne 1 ]]; then
		ok=false
	fi
	first_line=$(head -n 1 testfile)
	if [[ "$first_line" != *"Error"* ]]; then
		ok=false
	fi
	
	if [ "$ok" = true ]; then
		echo -en "${GREEN}1.OK ${NC}"
	else
		echo -en "${RED}1.KO ${NC}"
	fi
}

test_pipex() {
	test_name=$1
	infile=$2
	cmd1=$3
	cmd2=$4
	outfile=$5

	ok=true

	delete_files
	(< $infile $cmd1 | $cmd2 > shelloutfile) 2> shellerrorfile
	cmpstatus=$?
	sed -i 's|\.\/pipex_teter\.sh: line [0-9]\+: ||g' shellerrorfile

	./pipex "$infile" "$cmd1" "$cmd2" "$outfile" 2> errorfile
	status=$?
	
	if [ $status -ne $cmpstatus ]; then
		ok=false
		echo "" >> traces
		echo "test $test_name" >> traces
		echo "./pipex $infile $cmd1 $cmd2 $outfile" >> traces
		echo "test $test_name" >> traces
		echo "expected exit status $cmpstatus" >> traces
		echo "got exit status $status" >> traces
	fi

	if [ -f "outfile" ] && [ -f "shelloutfile" ]; then
		if ! cmp -s "outfile" "shelloutfile"; then
			ok=false
			echo "" >> traces
			echo "test $test_name" >> traces
			echo "./pipex $infile $cmd1 $cmd2 $outfile" >> traces
			echo "diferences outfile <	> shelloutfile" >> traces
			diff -y --suppress-common-lines outfile shelloutfile >> traces
		fi
	fi

	if ! cmp -s "errorfile" "shellerrorfile"; then
		ok=false
		echo "" >> traces
		echo "test $test_name" >> traces
		echo "./pipex $infile $cmd1 $cmd2 $outfile" >> traces
		echo "diferences errorfile <	> shellerrorfile" >> traces
		diff -y --suppress-common-lines errorfile shellerrorfile >> traces
	fi

	if [ "$ok" = true ]; then
		echo -en "${GREEN}$test_name.OK ${NC}"
	else
		echo -en "${RED}$test_name.KO ${NC}"
	fi
	delete_files
}

print_header

rm -f traces

test_1
test_pipex "2" "noexiste" "grep hello" "wc" "outfile"
create_infile
test_pipex "3" "infile" "ls ../" "ls ../" "outfile"
test_pipex "4" "infile" "grep hello" "wc" "outfile"
test_pipex "5" "noexiste" "grep hello" "wc" "outfile"
test_pipex "6" "infile" "ls" "ls" "noexiste/noexiste"
rm -f infile
echo

if [ -e traces ]; then
	echo -e "${ORANGE}
Traces:"
	cat traces
	echo -e "${NC}"
else
	echo -e "${GREEN}
All tests passed${NC}"
fi

rm -f traces

# ./pipex Makefile "awk '{ print$1 }'" "wc" outfile