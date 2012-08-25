Infrastructure    {#infrastructure}
==============

\tableofcontents

  - \subpage homepage
  - \subpage wiki
  - \subpage repositories for software packages and documents
  - \subpage virtual_machines
  - \subpage pandora_deployment

\section network_configuration Network configuration

|  |  |
|------------------|------------------|
| CIDR             | 134.95.11.128/27 |
| Subnet mask      | 255.255.255.224  |
| Standard Gateway | 134.95.11.129    |
| Nameserver       | 134.95.127.1, 134.95.129.23, 134.95.19.48, 134.95.167.20 |


\section servers Servers

| Name                         | Hosted service     |
|------------------------------|--------------------|
| prometheus1.uni-koeln.de     | Production system  |
| prometheus2.uni-koeln.de     | Development system |
| prometheus-db1               | Database server    |
| prometheus-web1              | Web server         |
| prometheus-srv1.uni-koeln.de | Redmine            |
| prometheus-srv2.uni-koeln.de | ??                 |
| prometheus-srv3.uni-koeln.de | Jekyll Commander   |
| prometheus-srv4.uni-koeln.de | ??                 |


\section domains Domains

| Name                         | Address       |
|------------------------------|---------------|
| prometheus-bildarchiv.de     | 134.95.19.39  |
| prometheus-web.uni-koeln.de  | 134.95.19.39  |
| prometheus-db1.uni-koeln.de  | 134.95.80.95  |
| prometheus-web1.uni-koeln.de | 134.95.80.96  |
| prometheus-srv1.uni-koeln.de | 134.95.80.160 |
