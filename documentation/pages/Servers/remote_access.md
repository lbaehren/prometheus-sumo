Remote access    {#servers_remote_access}
=============

Connections from outside the `uni-koeln.de` domain need to go through a portal machine (`dialog.rrz.uni-koeln.de`).

~~~~
Host dialog_koeln
   User lbaehren
   Hostname dialog.rrz.uni-koeln.de
   ForwardAgent yes
   ForwardX11 no
   ServerAliveInterval 300

Host prom-srv1
   ProxyCommand ssh dialog_koeln nc %h %p
   Hostname prometheus-srv1.uni-koeln.de
   User lbaehren
   ForwardAgent yes
   ForwardX11 no
   ServerAliveInterval 300
~~~~

