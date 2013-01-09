Servers    {#servers}
=======

\tableofcontents

\section network_configuration Network configuration

|  |  |
|------------------|------------------|
| CIDR             | 134.95.11.128/27 |
| Subnet mask      | 255.255.255.224  |
| Standard Gateway | 134.95.11.129    |
| Nameserver       | 134.95.127.1, 134.95.129.23, 134.95.19.48, 134.95.167.20 |


\section server_machines Server names and hosted services

* \subpage servers_remote_access

| IP address      | Hostname                     | Hosted service             |
|-----------------|------------------------------|----------------------------|
| 134.95.19.39    | www.prometheus-bildarchiv.de | \ref image_archive         |
| 134.95.80.11    | \subpage servers_prom1 | Production system for \ref pandora |
| 134.95.80.12    | \subpage servers_prom2 | Development system for \ref pandora |
| 134.95.80.13    | prometheus-test.uni-koeln.de | [pandora-devel](http://prometheus-test.uni-koeln.de/pandora-devel) |
| 134.95.80.95    | \subpage servers_db1  | Database server                      |
| 134.95.80.96    | \subpage servers_web1 | Web server                           |
| 134.95.80.160   | \subpage servers_srv1 | \ref subversion server, \ref redmine \ref issue_tracker, \ref virtual_machines |
| 134.95.80.161   | \subpage servers_srv2 | prometheus-app.uni-koeln.de, Mail-Server |
| 134.95.80.162   | \subpage servers_srv3 | \ref homepage, \ref JekyllCommander, \ref servers_srv3_doc "Documentation" |
| 134.95.80.163   | \subpage servers_srv4 | \ref dilps databases |
| 134.95.167.124  | prometheus.khi.uni-koeln.de  |  |
| 134.95.167.125  | prometheus2.khi.uni-koeln.de |  |


\section virtual_hosts Virtual Hosts

Support for VM-Environment: vmqware@uni-koeln.de

\verbatim
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
\endverbatim

\section servers_references References

* [The seven deadly myths about virtualisation](http://features.techworld.com/virtualisation/119936/the-seven-deadly-myths-about-virtualisation)
* [10 Years of Virtual Machine Performance (Semi) Demystified](http://www.engineyard.com/blog/2009/10-years-of-virtual-machine-performance-semi-demystified)
