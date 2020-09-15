#!/bin/bash

# bulk editing :)
for filename in "$@"
do
    number=$(tail -n 1 $filename 2>/dev/null)            # read the number (hide errors)
    if [[ $? -eq 0 ]]; then                              # check if file exists (0 if yes)
        if [[ -z $(ln $filename $filename.lock 2>&1) ]]  # ln output is empty if there was no lockfile
        then
            let number+=1                                # increase the value
            echo $number >> $filename                    # append to the file
            rm $filename.lock                            # remove the lock
            echo "Appended $number to the file"
        else
            echo "Error: $filename is already opened"
        fi
    fi
done
