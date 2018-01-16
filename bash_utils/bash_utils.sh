#!/bin/bash
# Some bash utilities I use(d)
# Remember to allow permission for executable! (chmod +x bash_utils.sh)

set -euo pipefail # fail fast

# default values for options (stored in variables)
OPTION_E=1
OPTION_N=1

# specify options while launching the bash script
while getopts h?:D:E:N: option; do
    case "${option}" in
    h|\?)
        echo "usage: $0 -E <option E> -N <option N>"
        exit 0
        ;;
    E)
        OPTION_E=${OPTARG}
        ;;
    N)
        OPTION_N=${OPTARG}
        ;;
    esac
done

# Write to both terminal and a logfile
logfile_name="logfile.txt"
echo "Writing both to terminal and to logfile" | tee ${logfile_name}
echo "Appending lines both to terminal and to logfile" | tee -a ${logfile_name}

# How to check GCC version, ex. for usage in MATLAB
GCC_VER=$(gcc --version | head -n1 | cut -d" " -f4)
if [ ${GCC_VER} != 4.9.3 ]
then
    echo "Error: cannot use current GCC version with MATLAB.
    Please change to gcc 4.9.3 via sudo update-alternatives --config gcc
    Aborting." | tee -a ${logfile_name}
    exit -1
fi

# Running MATLAB function function_name with minimal impact (Assuming we are in the function's folder)
exec_matlab="matlab -nodisplay -nodesktop -r 'try function_name(par1,...,parN); catch; end; quit'"
eval $exec_matlab

# Find a specific string in a file, and insert another string (on a newline) after every occurency
FIND_AFTER="Insert"
STRING_TO_INSERT="Example string to be inserted after every 'Insert' (case sensitive)"

sed -i "/${FIND_AFTER}/a \
${STRING_TO_INSERT} " example.txt