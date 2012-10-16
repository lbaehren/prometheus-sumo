Coding guidelines    {#coding_guidelines}
=================

\tableofcontents

\li [Linux kernel coding style](http://www.kernel.org/doc/Documentation/CodingStyle)
\li [Ruby Style Guide](http://www.rubygarden.org/Ruby/page/show/RubyStyleGuide)
\li [GNU Coding Standards](http://www.gnu.org/prep/standards/standards.html)
\li [Google C++ Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml)

\section guidelines_general General

\li always indent by 2 spaces, except where not (see below); needless to say: don't ever use tabs!
\li always align beginning and end of a block
\li try hard to keep line length below 80 characters (see below for details)
\li coding (and commenting) language is english; i.e., variable, method, class, and module names, as well as CSS class names and IDs, are meaningful english words (or sensible abbreviations thereof)
\li use full-line comments to explain the algorithm; use end-of-line comments to point out subtleties and oddities
\li comment anything that has puzzled or tricked you
\li consider whether it's better to rewrite than to comment
\li check the spelling, syntax, and sanity - and consistency! - of your documentation
\li use RDoc simple markup in comments if appropriate
\code
_italic_
*bold*
+typewriter+
\endcode
\li use tags (common: `NOTE`, `TODO`, `FIXME`, ...; rails specific: EdgeRails, Rails2.0, ...)
\code
# NOTE: some note...

# in {EdgeRails} we have...
\endcode
in HTML text:
\code
<p>[TODO] project description...</p>
\endcode
\li always use `\\A` and `\\z`, not `^` and `$`, as string boundary anchors; use `\\z`, not `\\Z`, to indicate "end of string"
\li consider matching arbitrary whitespace (`\s`), rather than specific whitespace characters
\li use capturing parentheses only when you intend to capture; always give captured substrings proper names
\li prevent useless backtracking!
\li raise/throw exceptions instead of returning special values or setting flags
\li place original code inline, place duplicated code in a subroutine, place duplicated subroutines in a module
\li don't optimize code - benchmark it; don't optimize data structures - measure them; don't optimize applications - profile them
\li be careful to preserve semantics when refactoring syntax
\li don't be clever; if you must rely on cleverness, encapsulate it
\li be consistent!

Find files that have trailing whitespace:
\code
find . -type f -exec egrep -l " +$" {} \;
\endcode
Remove trailing whitespaces from files:
\code
for FILE in $FILES
{
  cat $FILE | sed -e "s/ \{1,\}$//" > output.tmp
  mv output.tmp $FILE
}
\endcode

\section guidelines_ruby Ruby & Rails

\section guidelines_html HTML

\li Indent nested block-level elements
\verbatim
<ul>
  <li>...</li>
  <li>...</li>
</ul>
\endverbatim
\li Treat block-level elements as blocks if content exceeds the 80 character line length limit
\verbatim
<p>
  ...some long text...
</p>
\endverbatim
not
\verbatim
<p>...some long text...</p>
\endverbatim

\section guidelines_javascript Javascript


\section guidelines_css CSS

\li Be as specific as necessary, be as general as possible; e.g., an ID is already as specific as it gets, hence no need to specify the element to which it applies, too
\li Prefer \c - over \c _ as separators in class names and IDs
\li Color goes with background-color (and vice versa); use inherit in case you don't want to (or can't) specify an explicit value
\li Use \c !important only where absolutely necessary
\li Put opening curly on same line as selector(s)
\verbatim
foo.bar, #baz {
  quix:             quux;
}
\endverbatim
not
\verbatim
foo.bar, #baz
{
  quix:             quux;
}
\endverbatim
\li Align attribute values at the same column file-wide, but at least at column 21 (which results from \c background-color, which is typically the longest attribute used)
\li Wrap multiple selectors on several lines if they exceed 80 characters in length; align/group logically where appropriate
