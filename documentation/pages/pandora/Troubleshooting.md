
Troubleshooting    {#pandora_troubleshooting}
===============

\tableofcontents

\section pandora_troubleshooting_specs Running the specs

  \b Problem: Specs fail, because resources have PID 0.

  \li \b Description: In der Datenbank der Test-Umgebung ist \c Resource#pid nicht vom Typ String, wie erwartet, sondern vom Typ Integer.
  \verbatim
  >> Resource.column_by_name(:pid).type
  => :integer
  \endverbatim
  \li \b Solution: The table \a Resources needs to be created anew.
  \verbatim
  rake db:test:setup  # fängt quasi bei "Null" wieder an
  \endverbatim

