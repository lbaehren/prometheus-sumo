RSpec    {#rspec}
=====

\tableofcontents

The RSpec tool is a Ruby package that lets you build a specification alongside your software. This specification is actually a test that describes the behavior of your system. Here's the flow for development with RSpec:

* You write a test. This test describes the behavior of a small element of your system.
* You run the test. The test fails because you have not yet built the code for that part of your system. This important step tests your test case, verifying that your test case fails when it should.
* You write enough code to make the test pass.
* You run the tests and verify that they pass.

In essence, an RSpec developer turns test cases from red (failing) to green (passing) all day. It's a motivating process.

\section rspec_ref References

* [Behavior-driven testing with RSpec](http://www.ibm.com/developerworks/web/library/wa-rspec)
* [RSpec Best Practices](http://www.methodsandtools.com/tools/tools.php?rspec)