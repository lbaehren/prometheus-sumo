Apache Log Files    {#apache_logs}
================

\tableofcontents

Web server access logs are an excellent source of information about what your site's visitors are up to. The information on separate visitors is all mixed together, though, and for all but the smallest sites the raw access logs are too large to read directly. What you need is log analysis software to make the information in the log more easily accessible.

\section apache_logs_structure Log File Structure

Most web servers store their access log in what is called the "common log
format." Each time a user requests a file from the server, a line containing
the following fields is added to the end of the log file:

\li **host** -- This is either the IP address (like `207.71.222.231`) or the corresponding hostname (like pm9-31.sba1.avtel.net) of the remote user requesting the page. For performance reasons, many web servers are configured not to do hostname lookups on the remote host. This means that all you end up with in the log file is a bunch of IP addresses. A bit later in this chapter, you'll develop a Perl script that you can use to convert those IP addresses into hostnames.

\li **identd result** -- This is a field for logging the response returned by the remote user's identd server. Almost no one actually uses this; in every web log I've ever seen, this field is always just a dash (`-`). 

\li **authuser** -- If you are using basic 'ecHTTP authentication (which we'll be talking about in Chapter 19) to restrict access to some of your web documents, this is where the username of the authenticated user for this transaction will be recorded. Otherwise, it will be just a dash (`-`).

\li **date and time** -- Next comes a date and time string inside square brackets, like: `[06/Jul/1999:00:09:12 -0700]`. That's the day of the month, the abbreviated month name, and the four-digit year, all separated by slashes. Next come the time (expressed in 24-hour format, so 11:30 P.M. would be 23:30:00) and a time-zone offset (in this example, `-0700`, because the web server this log was from was using Pacific Daylight Time, which is seven hours behind Universal Time/Greenwich Mean Time).

\li **request** -- This is the actual request sent by the remote user, enclosed in double quotes. Normally it will look something like: `"GET / HTTP/1.0"`. The GET part means it is a GET request (as opposed to a POST or a HEAD request). The next part is the path of the URL requested; in this case, the default page in the server's top-level directory, as indicated by a single slash (/). The last part of the request is the protocol being used, at the time of this writing typically HTTP/1.0 or HTTP/1.1.

\li **status code** -- This is the status code returned by the server; by definition this will be a three-digit number. A status code of 200 means everything was handled okay, 304 means the document has not changed since the client last requested it, 404 means the document could not be found, and 500 indicates that there was some sort of server-side error. (More detail on the various status codes can be found in RFC 1945, which describes the HTTP/1.0 protocol. See http://www.w3.org/Protocols/rfc1945/rfc1945.)

\li **bytes sent** -- The amount of data returned by the server, not counting the header line.

An extended version of this log format, often referred to as the "combined" format, includes two additional fields at the end:

\li **referer** -- The referring page, if any, as reported by the remote user's browser. Note that referer is consistently misspelled (with a single "r" in the middle) in the HTTP specification, and in the name of the corresponding environment variable.

\li **user agent** -- The user agent reported by the remote user's browser. Typically, this is a string describing the type and version of browser software being used.

Assuming you have control over your web server's configuration, or can get your ISP to modify it for you, the combined format's extra fields can provide some very interesting information about the users visiting your site. The log analysis script described in this chapter will work with either format, however.

\section apache_logs_processing Processing log files

\subsection apache_logs_processing_php ... using PHP

\code
function processLine($line) {
    $matches = array();
 
    // process the string. This regular expression was adapted from http://oreilly.com/catalog/perlwsmng/chapter/ch08.html
    preg_match('/^(\S+) (\S+) (\S+) \[([^:]+):(\d+:\d+:\d+) ([^\]]+)\] "(\S+) (.+?) (\S+)" (\S+) (\S+) "([^"]+)" "([^"]+)"$/', $line, $matches);
 
    if (isset($matches[0])) {
        return array('fullString' => $matches[0],
                     'remoteHost' => $matches[1],
                     'identUser' => $matches[2],
                     'authUser' => $matches[3],
                     'date' => $matches[4],
                     'time' => $matches[5],
                     'timezone' => $matches[6],
                     'method' => $matches[7],
                     'url' => $matches[8],
                     'protocol' => $matches[9],
                     'status' => $matches[10],
                     'bytes' => $matches[11],
                     'referrer' => $matches[12],
                     'userAgent' => $matches[13]
        );
    } else {
        return array();
    }
}
\endcode

\subsection apache_logs_processing_cpp ... using C++

\li prometheus::statistics::ApacheCombinedLog
\li \ref testApacheLogs.cc


  \code
regex expression("^([0-9]+)(\\-| |$)(.*)$");

// process_ftp:
// on success returns the ftp response code, and fills
// msg with the ftp response message.
int process_ftp(const char* response, std::string* msg)
{
   cmatch what;
   if(regex_match(response, what, expression))
   {
      // what[0] contains the whole string
      // what[1] contains the response code
      // what[2] contains the separator character
      // what[3] contains the text message.
      if(msg)
         msg->assign(what[3].first, what[3].second);
      return ::atoi(what[1].first);
   }
   // failure did not match
   if(msg)
      msg->erase();
   return -1;
}
\endcode

\section apache_logs_references References

\li [Analyzing Apache Log Files](http://www.the-art-of-web.com/system/logs)
\li [Parsing web access logs](http://oreilly.com/catalog/perlwsmng/chapter/ch08.html) -- John Callender (2001) Perl for Web Site Management.
\li [Exploring the Apache access_log](http://www.intuitive.com/wicked/84-exploring-apache-access_log-shell-script.shtml)
\li [Importing Apache (httpd) logs into MySQL](http://www.startupcto.com/server-tech/apache/importing-apache-httpd-logs-into-mysql)