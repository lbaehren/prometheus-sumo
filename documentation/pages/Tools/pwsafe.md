pwsafe    {#pwsafe}
======

\tableofcontents

pwsafe is a unix commandline program that manages encrypted password databases.

\section pwsafe_usage Usage

\code
/var/local/prometheus/bin/pwsafe.rb [-h|--help] [options] <file> [<realm>]
\endcode

Actions are initiated through one of the following command-line options:

| Option       | Action                             |
|--------------|------------------------------------|
| -l, --list   | List all entries in the file       |
| -s, --set    | Set secret for the specified entry |
| -D, --delete | Delete the specified entry         |

Without any action, the secret is sent to STDOUT -- \b unencrypted! If realm
is not given, it will be asked for interactively.

\section pwsafe_features Features

  * Pure command-line operation if desired (good for remote access over ssh)
  * or can interact with X11 selection & clipboard.
  * Portable, endianess-clean, misaligned-access-free C++. Compiles cleanly on linux, *bsd, macos x, solaris.
  * Compatible with CounterPane's PasswordSafe Win32 program versions 2.x and 1.x.

