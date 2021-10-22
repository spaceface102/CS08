#!/usr/bin/python3

import sys
import os

def main(fname : str, recipe : str) -> None:
    '''
    Intended to be used with automatic dependency
    building makefiles. The problem it seeks to solve
    is choosing a directory into where to dump the object
    files.
    ex. gcc -M -MP -MF deps/main.d -MT build/main.o main.c
    
    fname is the name of the file produced by the above
    gcc -M (or -MM) -MP -MF <fname> -MT <target> combo

    recipe defines, well, the recipe for the automatically
    created rule.
    '''
    new_depfile_name = ".temp_dep_file_"
    new_depfile_name += fname.replace("/", "")
    base_depfile = open(fname, "r")
    new_depfile = open(new_depfile_name, "w")


    for line in base_depfile:
        new_depfile.write(line)
        if line[-2] != '\\': #line[-1] is always '/n'
            new_depfile.write("\t")
            new_depfile.write(recipe)
            new_depfile.write("\n")
            break

    #write the rest of the file
    for line in base_depfile:
        new_depfile.write(line)

    new_depfile.close()
    base_depfile.close()

    #overwrite base_depfile with new dep file
    #that also includes the specific recipe
    os.rename(new_depfile_name, fname)

if __name__ == "__main__":
    if len(sys.argv) > 2:
        main(sys.argv[1], sys.argv[2])
    else:
        print(sys.argv[0] + " <dep fname> <recipe (eg gcc -c)>")