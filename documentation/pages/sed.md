Handy one-liners for SED    {#sed}
========================

\tableofcontents

The **sed** utility reads the specified files, or the standard input if no files are
specified, modifying the input as specified by a list of commands.  The input is then
written to the standard output.

A single command may be specified as the first argument to sed.  Multiple commands
may be specified by using the -e or -f options.  All commands are applied to the
input in the order they are specified regardless of their origin.

\section sed_file_spacing File spacing

\li double space a file
\code
 sed G
\endcode

\li double space a file which already has blank lines in it. Output file
should contain no more than one blank line between lines of text.
\code
 sed '/^$/d;G'
\endcode

\li triple space a file
\code
 sed 'G;G'
\endcode

\li undo double-spacing (assumes even-numbered lines are always blank)
\code
 sed 'n;d'
\endcode

\section sed_numbering Numbering

\li number each line of a file (simple left alignment). Using a tab (see note on `\t` at end of file) instead of space will preserve margins.
\verbatim
 sed = filename | sed "N;s/\n/\t/"
\endverbatim

\li number each line of a file (number on left, right-aligned)
\verbatim
 sed = filename | sed 'N; s/^/     /; s/ *\(.\{6,\}\)\n/\1  /'
\endverbatim

\li number each line of file, but only print numbers if line is not blank
\code
 sed '/./=' filename | sed "/./N; s/\n/ /"
\endcode

\li count lines (emulates `wc -l`)
\code
 sed -n '$='
\endcode

\section sed_text Text conversion and substitution

\li IN UNIX ENVIRONMENT: convert DOS newlines (CR/LF) to Unix format
\code
 sed 's/.$//'               # assumes that all lines end with CR/LF
 sed 's/^M$//'              # in bash/tcsh, press Ctrl-V then Ctrl-M
 sed 's/\x0D$//'            # gsed 3.02.80, but top script is easier
\endcode

\li IN UNIX ENVIRONMENT: convert Unix newlines (LF) to DOS format
\code
 sed "s/$/`echo -e \\\r`/"            # command line under ksh
 sed 's/$'"/`echo \\\r`/"             # command line under bash
 sed "s/$/`echo \\\r`/"               # command line under zsh
 sed 's/$/\r/'                        # gsed 3.02.80
\endcode

\li IN DOS ENVIRONMENT: convert Unix newlines (LF) to DOS format
\code
 sed "s/$//"                          # method 1
 sed -n p                             # method 2
\endcode

\li IN DOS ENVIRONMENT: convert DOS newlines (CR/LF) to Unix format
Cannot be done with DOS versions of sed. Use "tr" instead.
\code
 tr -d \r <infile >outfile            # GNU tr version 1.22 or higher
\endcode

\li delete leading whitespace (spaces, tabs) from front of each line
aligns all text flush left
\code
 sed 's/^[ \t]*//'                    # see note on '\t' at end of file
\endcode

\li delete trailing whitespace (spaces, tabs) from end of each line
\code
 sed 's/[ \t]*$//'                    # see note on '\t' at end of file
\endcode

\li delete BOTH leading and trailing whitespace from each line
\code
 sed 's/^[ \t]*//;s/[ \t]*$//'
\endcode

\li insert 5 blank spaces at beginning of each line (make page offset)
\code
 sed 's/^/     /'
\endcode

\li align all text flush right on a 79-column width
\code
 sed -e :a -e 's/^.\{1,78\}$/ &/;ta'  # set at 78 plus 1 space
\endcode

\li center all text in the middle of 79-column width. In method 1,
spaces at the beginning of the line are significant, and trailing
spaces are appended at the end of the line. In method 2, spaces at
the beginning of the line are discarded in centering the line, and
no trailing spaces appear at the end of lines.
\code
 sed  -e :a -e 's/^.\{1,77\}$/ & /;ta'                     # method 1
 sed  -e :a -e 's/^.\{1,77\}$/ &/;ta' -e 's/\( *\)\1/\1/'  # method 2
\endcode

\li substitute (find and replace) "foo" with "bar" on each line
\code
 sed 's/foo/bar/'             # replaces only 1st instance in a line
 sed 's/foo/bar/4'            # replaces only 4th instance in a line
 sed 's/foo/bar/g'            # replaces ALL instances in a line
 sed 's/\(.*\)foo\(.*foo\)/\1bar\2/' # replace the next-to-last case
 sed 's/\(.*\)foo/\1bar/'            # replace only the last case
\endcode

\li substitute "foo" with "bar" ONLY for lines which contain "baz"
\code
 sed '/baz/s/foo/bar/g'
\endcode

\li substitute "foo" with "bar" EXCEPT for lines which contain "baz"
\code
 sed '/baz/!s/foo/bar/g'
\endcode

\li change "scarlet" or "ruby" or "puce" to "red"
\code
 sed 's/scarlet/red/g;s/ruby/red/g;s/puce/red/g'   # most seds
 gsed 's/scarlet\|ruby\|puce/red/g'                # GNU sed only
\endcode

\li reverse order of lines (emulates "tac")
bug/feature in HHsed v1.5 causes blank lines to be deleted
\code
 sed '1!G;h;$!d'               # method 1
 sed -n '1!G;h;$p'             # method 2
\endcode

\li reverse each character on the line (emulates "rev")
\code
 sed '/\n/!G;s/\(.\)\(.*\n\)/&\2\1/;//D;s/.//'
\endcode

\li join pairs of lines side-by-side (like "paste")
\code
 sed '$!N;s/\n/ /'
\endcode

\li if a line ends with a backslash, append the next line to it
\code
 sed -e :a -e '/\\$/N; s/\\\n//; ta'
\endcode

\li if a line begins with an equal sign, append it to the previous line
and replace the "=" with a single space
\code
 sed -e :a -e '$!N;s/\n=/ /;ta' -e 'P;D'
\endcode

\li add commas to numeric strings, changing "1234567" to "1,234,567"
\code
 gsed ':a;s/\B[0-9]\{3\}\>/,&/;ta'                     # GNU sed
 sed -e :a -e 's/\(.*[0-9]\)\([0-9]\{3\}\)/\1,\2/;ta'  # other seds
\endcode

\li add commas to numbers with decimal points and minus signs (GNU sed)
\code
 gsed ':a;s/\(^\|[^0-9.]\)\([0-9]\+\)\([0-9]\{3\}\)/\1\2,\3/g;ta'
\endcode

\li add a blank line every 5 lines (after lines 5, 10, 15, 20, etc.)
\code
 gsed '0~5G'                  # GNU sed only
 sed 'n;n;n;n;G;'             # other seds
\endcode
