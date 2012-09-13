#!/bin/sh

##______________________________________________________________________________
## Get the list of files which have changed since the version used as baseline

if [ $1 ]
then
  echo "--> Building list of changed files ..."
  FILES=`git diff --name-only $1`
  echo "==> DONE"
else
  echo "No baseline version provided - please name one!"
  exit
fi

##______________________________________________________________________________
## Go through the list of identified files and check if they contain trailing
## whitespaces.

for FILE in $FILES
{
  if [ -f $FILE ] ;
  then
    echo "--> Processing file $FILE ..."
    git diff $1 "$FILE" | grep -q "^+.*[^-][[:space:]]$" && {
      echo " !! Trailing whitespace detected !!" 1>&2;
    }
  else
    echo "--> Skipping file $FILE - no longer present!"
  fi
}
