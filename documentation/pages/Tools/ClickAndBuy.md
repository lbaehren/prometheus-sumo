ClickandBuy    {#clickandbuy}
===========

\tableofcontents

[ClickandBuy](http://www.clickandbuy.com) is one of the leading payment systems on the internet. More than 16,000 merchants and 13 million users benefit from this complete service in 30 countries, which includes 120 different currencies and 50 different payment methods.

\section clickandbuy_api API

The ClickandBuy API (Application Programming Interface) is an interface which
your e-commerce site uses to communicate with the ClickandBuy system for
processing transactions and other API functions.

\subsection clickandbuy_api_mms Merchant Messaging Service (MMS)

The Merchant Messaging Service (MMS) provides you with real-time information on status changes on transactions and makes sure that your system is up-to-date. This is why we recommend considering this feature for the integration of the ClickandBuy API.

The transmission takes places as \ref xml (HTTP POST parameter "xml") to the HTTPS URL of a script on your server that receives the data and evaluates it accordingly. You can store the MMS PUSH URL in the Service Area in the project data of your ClickandBuy account.

Each status information, a so called event, is assigned with a unique ID. In this way the status of a transaction can be traced without any problems.

\subsection clickandbuy_api_testing Testing

To test whether the integration of the ClickandBuy API was successful, you require an active sandbox account. The sandbox system is technically identical with the productive system of the ClickandBuy API. Important exception: Payments are only simulated and, self-evidently, you don't pay any fees for the transactions.

To create your sandbox account you require a registered productive account. If this requirement is met, you are only three steps away from your sandbox account:

1. Log into the Merchant Area of your productive account via [www.clickandbuy.com](http://www.clickandbuy.com).
2. After logging in click on the menu item "Sandbox > Create sandbox account" in "Tools".
3. Follow the instructions on the screen to create a sandbox account for merchants (providers) or surfers (purchasers).

Note: To properly test your integration, we recommend creating both account types, for merchants and surfers. In this way you are able to ensure the correct processing of payment transactions from a merchant's as well as a customer's point of view.

\section clickandbuy_references References

* [clickandbuy.com](http://www.clickandbuy.com)
* [API integration](http://www.clickandbuy.com/WW_en/merchants/integration/api-integration/quick-overview.html)
* [API Manual](http://www.clickandbuy.com/WW_en/merchants/integration/api-integration/api-manual.html)


