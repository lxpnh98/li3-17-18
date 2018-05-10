cd "${0%/*}/src" # para correr programa com o mesmo argumento
valgrind --leak-check=full ./program $1 > /dev/null
