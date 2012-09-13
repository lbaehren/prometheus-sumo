Infrastructure    {#infrastructure}
==============

\tableofcontents

  - \subpage homepage
  - \subpage wiki
  - \subpage issue_tracker
  - \subpage repositories for software packages and documents
  - \subpage virtual_machines
  - \subpage pandora_deployment
  - \subpage pwsafe

\section network_configuration Network configuration

|  |  |
|------------------|------------------|
| CIDR             | 134.95.11.128/27 |
| Subnet mask      | 255.255.255.224  |
| Standard Gateway | 134.95.11.129    |
| Nameserver       | 134.95.127.1, 134.95.129.23, 134.95.19.48, 134.95.167.20 |


\section servers Servers

| Name                         | IP address   | Hosted service     |
|------------------------------|--------------|--------------------|
| www.prometheus-bildarchiv.de | 134.95.19.39 | [Image archive](http://www.prometheus-bildarchiv.de) |
| prometheus1.uni-koeln.de     | 134.95.80.11 | Production system  |
| prometheus2.uni-koeln.de     | 134.95.80.12 | Development system |
| prometheus-test.uni-koeln.de | 134.95.80.13 |                    |
| prometheus-db1               | 134.95.80.95 | Database server    |
| prometheus-web1              | 134.95.80.96 | Web server         |
| prometheus-srv1.uni-koeln.de | 134.95.80.160 | [Trac](http://prometheus-srv.uni-koeln.de/trac/pandora) |
| prometheus-srv2.uni-koeln.de | 134.95.80.161 | prometheus-app.uni-koeln.de |
| prometheus-srv3.uni-koeln.de | 134.95.80.162 | Jekyll Commander  |
| prometheus-srv4.uni-koeln.de | 134.95.80.164 |  |

http://prometheus-test.uni-koeln.de/pandora-devel

\section virtual_hosts Virtual Hosts

    prometheus.khi.uni-koeln.de
        pandora
        pandora-devel
        pandora-test
        assets0.pandora
        assets1.pandora
        assets2.pandora
        assets3.pandora
        assets0.pandora-devel
        assets1.pandora-devel
        assets2.pandora-devel
        assets3.pandora-devel
        assets0.pandora-test
        assets1.pandora-test
        assets2.pandora-test
        assets3.pandora-test
        rlv
        foo
        bar
    prometheus.uni-koeln.de
        pandora
        pandora-devel
        pandora-test
        assets0.pandora
        assets1.pandora
        assets2.pandora
        assets3.pandora
    prometheus-test.uni-koeln.de
        pandora
        pandora-devel
        pandora-test
        assets0.pandora-devel
        assets1.pandora-devel
        assets2.pandora-devel
        assets3.pandora-devel
        assets0.pandora-test
        assets1.pandora-test
        assets2.pandora-test
        assets3.pandora-test
