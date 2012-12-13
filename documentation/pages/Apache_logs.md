Apache Log Files    {#apache_logs}
================

\tableofcontents

Web server access logs are an excellent source of information about what your site's visitors are up to. The information on separate visitors is all mixed together, though, and for all but the smallest sites the raw access logs are too large to read directly. What you need is log analysis software to make the information in the log more easily accessible.

\section apache_logs_access Access Log

The server access log records all requests processed by the server. The location and content of the access log are controlled by the CustomLog directive. The LogFormat directive can be used to simplify the selection of the contents of the logs. This section describes how to configure the server to record information in the access log.

Of course, storing the information in the access log is only the start of log management. The next step is to analyze this information to produce useful statistics. Log analysis in general is beyond the scope of this document, and not really part of the job of the web server itself. For more information about this topic, and for applications which perform log analysis, check the Open Directory or Yahoo.

Various versions of Apache httpd have used other modules and directives to control access logging, including mod_log_referer, mod_log_agent, and the TransferLog directive. The CustomLog directive now subsumes the functionality of all the older directives.

The format of the access log is highly configurable. The format is specified using a format string that looks much like a C-style printf(1) format string. Some examples are presented in the next sections. For a complete list of the possible contents of the format string, see the mod_log_config documentation.

\subsection apache_logs_access_common Common Log Format

A typical configuration for the access log might look as follows.

\verbatim
LogFormat "%h %l %u %t \"%r\" %>s %b" common
CustomLog logs/access_log common
\endverbatim

This defines the nickname common and associates it with a particular log format string. The format string consists of percent directives, each of which tell the server to log a particular piece of information. Literal characters may also be placed in the format string and will be copied directly into the log output. The quote character (") must be escaped by placing a back-slash before it to prevent it from being interpreted as the end of the format string. The format string may also contain the special control characters `\n` for new-line and `\t` for tab.

The CustomLog directive sets up a new log file using the defined nickname. The filename for the access log is relative to the [ServerRoot](http://httpd.apache.org/docs/1.3/mod/core.html#serverroot) unless it begins with a slash.

The above configuration will write log entries in a format known as the Common Log Format (CLF). This standard format can be produced by many different web servers and read by many log analysis programs. The log file entries produced in CLF will look something like this:

\code
127.0.0.1 - frank [10/Oct/2000:13:55:36 -0700] "GET /apache_pb.gif HTTP/1.0" 200 2326
\endcode

Each part of this log entry is described below.

\li **IP address of the client (remote host)**
  \code 127.0.0.1 (%h) \endcode
  This is the IP address of the client (remote host) which made the request to the server. If HostnameLookups is set to On, then the server will try to determine the hostname and log it in place of the IP address. However, this configuration is not recommended since it can significantly slow the server. Instead, it is best to use a log post-processor such as logresolve to determine the hostnames. The IP address reported here is not necessarily the address of the machine at which the user is sitting. If a proxy server exists between the user and the server, this address will be the address of the proxy, rather than the originating machine.

\li **RFC 1413 identity of the client**
  \code - (%l) \endcode
  The "hyphen" in the output indicates that the requested piece of information is not available. In this case, the information that is not available is the RFC 1413 identity of the client determined by identd on the clients machine. This information is highly unreliable and should almost never be used except on tightly controlled internal networks. Apache httpd will not even attempt to determine this information unless IdentityCheck is set to On.

\li **userid of the person requesting the document**
  \code frank (%u) \endcode
  This is the userid of the person requesting the document as determined by HTTP authentication. The same value is typically provided to CGI scripts in the REMOTE_USER environment variable. If the status code for the request (see below) is 401, then this value should not be trusted because the user is not yet authenticated. If the document is not password protected, this entry will be "-" just like the previous one.

\li **Time that the server finished processing the request**
  \code [10/Oct/2000:13:55:36 -0700] (%t) \endcode
  The time that the server finished processing the request. The format is:
  \code
    [day/month/year:hour:minute:second zone]
    day = 2*digit
    month = 3*letter
    year = 4*digit
    hour = 2*digit
    minute = 2*digit
    second = 2*digit
    zone = (`+' | `-') 4*digit
  \endcode
  It is possible to have the time displayed in another format by specifying %{format}t in the log format string, where format is as in strftime(3) from the C standard library. 

\li **Request line from the client**
  \code "GET /apache_pb.gif HTTP/1.0" (\"%r\") \endcode
    The request line from the client is given in double quotes. The request line contains a great deal of useful information. First, the method used by the client is GET. Second, the client requested the resource /apache_pb.gif, and third, the client used the protocol HTTP/1.0. It is also possible to log one or more parts of the request line independently. For example, the format string "%m %U%q %H" will log the method, path, query-string, and protocol, resulting in exactly the same output as "%r".

\li **Status code sent by the server**
  \code 200 (%>s) \endcode
  This is the status code that the server sends back to the client. This information is very valuable, because it reveals whether the request resulted in a successful response (codes beginning in 2), a redirection (codes beginning in 3), an error caused by the client (codes beginning in 4), or an error in the server (codes beginning in 5). The full list of possible status codes can be found in the HTTP specification (RFC2616 section 10).

\li **Size of the object returned to the client**
  \code 2326 (%b) \endcode
  The last entry indicates the size of the object returned to the client, not including the response headers. If no content was returned to the client, this value will be "-". To log "0" for no content, use %B instead.

\subsection apache_logs_access_combined Combined Log Format

Another commonly used format string is called the Combined Log Format. It can be used as follows.

\code
LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-agent}i\"" combined
CustomLog log/acces_log combined
\endcode

This format is exactly the same as the Common Log Format, with the addition of two more fields. Each of the additional fields uses the percent-directive %{header}i, where header can be any HTTP request header. The access log under this format will look like:

\code
127.0.0.1 - frank [10/Oct/2000:13:55:36 -0700] "GET /apache_pb.gif HTTP/1.0" 200 2326 "http://www.example.com/start.html" "Mozilla/4.08 [en] (Win98; I ;Nav)"
\endcode

The additional fields are:

 \li **HTTP request header**
  \code "http://www.example.com/start.html" (\"%{Referer}i\") \endcode
  The "Referer" (sic) HTTP request header. This gives the site that the client reports having been referred from. (This should be the page that links to or includes /apache_pb.gif).
\li **User-Agent HTTP request header**
  \code "Mozilla/4.08 [en] (Win98; I ;Nav)" (\"%{User-agent}i\") \endcode
  The User-Agent HTTP request header. This is the identifying information that the client browser reports about itself. 

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

\li prometheus::statistics::ApacheLogfileEntry
\li prometheus::statistics::ApacheLogfileParser
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

\li [Apache log files](http://httpd.apache.org/docs/1.3/logs.html) (apache.org)
\li [Analyzing Apache Log Files](http://www.the-art-of-web.com/system/logs)
\li [Parsing web access logs](http://oreilly.com/catalog/perlwsmng/chapter/ch08.html) -- John Callender (2001) Perl for Web Site Management.
\li [Exploring the Apache access_log](http://www.intuitive.com/wicked/84-exploring-apache-access_log-shell-script.shtml)
\li [Importing Apache (httpd) logs into MySQL](http://www.startupcto.com/server-tech/apache/importing-apache-httpd-logs-into-mysql)
