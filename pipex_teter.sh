#!/bin/bash

ORANGE='\033[0;33m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

print_header() {
	echo -e "${GREEN} ____  __  ____  ____  _  _ ${RED}    ____  ____  ____  ____ ${NC}"
	echo -e "${GREEN}(  _ \(  )(  _ \(  __)( \/ )${RED}   (_  _)(  __)/ ___)(_  _)${NC}"
	echo -e "${GREEN} ) __/ )(  ) __/ ) _)  )  ( ${RED}     )(   ) _) \___ \  )(  ${NC}"
	echo -e "${GREEN}(__)  (__)(__)  (____)(_/\_)${RED}    (__) (____)(____/ (__) ${NC}"
}

create_infile() {
	echo "TESTER HORMIDEV" > infile
	echo "" >> infile
	echo "test 1 (argumentos invalidos)" >> infile
}

test_1() {
	ok=true

	first_line=$(./pipex 2>&1 | head -n 1)
	if [[ "$first_line" != *"Error"* ]]; then
		ok=false
	fi

	first_line=$(./pipex arg1 arg2 arg3 2>&1 | head -n 1)
	if [[ "$first_line" != *"Error"* ]]; then
		ok=false
	fi

	first_line=$(./pipex arg1 arg2 arg3 arg4 arg5 2>&1 | head -n 1)
	if [[ "$first_line" != *"Error"* ]]; then
		ok=false
	fi
	
	if [ "$ok" = true ]; then
		echo -e "${GREEN}1.OK${NC}"
	else
		echo -e "${RED}1.KO${NC}"
	fi
}
print_header
test_1