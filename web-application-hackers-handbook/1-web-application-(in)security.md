# Web Application (In)security

## The Evolution of Web Applications
In the early days, you had only websites which were static info. Web browsers were invented as a means of retrieving and displaying these documents. If someone compromised a server in these days, they'd deface the content or use it to host their own content.

These days, most sites are applications with a two-way flow of info between the server and browser. Most information is private and highly sensitive. Web apps bring with them new and unique security threats, as many developers don't properly understand web security (hi!).

## Benefits of Web Apps
- HTTP is lightweight and connectionless, providing resilience and avoiding the need for the server to hold open a network connection to every user.
- Every web user already has a browser, allowing for dynamic deploys and avoiding the need to distribute and manage separate client software.
- Browsers are highly functional, enabling rich and satisfying user interfaces.
- Core tech and languages are relativelysimple.

## Web App Security
As web apps have become more prolific, different security problems have arisen, and others have mostly gone away. By some measure, web app security is the most significant battleground between attackers and those with resources and data to defend.

Some websites say they're secure because they use SSL, or Payment Card Industry (PCI) standards. However, the majority of web apps are insecure, often being vulnerable to these categories of vulnerability:
- Broken Authentication: Some manner of defect in the application's login mechanism which enables guessing password, launching a brute-force attack or bypassing the login.
- Broken access controls: This involves cases where the app fails to properly protect access to its data and functionality, potentially enabling an attacker to view other users' sensitive data or carry out privileged actions.
- SQL injection: Lets an attacker submit crafter input to interfere with the apps interaction with databases. An attacker may be able to retrieve arbitrary data from the app, interfere with its logic or execute commands on the server.
- Cross-site scripting: Enables an attacker to target other users of the application, potentially gaining access to their data, performing unauthorised actions on their behalf or carrying out other attacks against them.
- Information leakage: This involves cases where an application divulges sensitive information that is of use to an attacker in developing an assault against the app.
- Cross-site request forgery: Means users can be induced to perform unintended actions within their user context and privilege level.

SSL is good, it protects the confidentiality and integrity of data in transit between browser and server, meaning it defends against eavesdroppers and can provide assurance about the identity of the web server.

The fundamental problem with web apps is that because the client is outside of the apps controls, users can submit arbitrary input to the server-side app. The app must assume that ALL input is potentially malicious so you have to take steps to ensure that attackers cannot use crafted input to compromise the app. This problem manifests itself in a few ways:
- Users can interfere with any piece of data transmitted between the client and the server including request params, cookies and HTTP headers. Any security controls on the client side such as input validation checks can be easily circumvented.
- Users can send requests in any sequence and can submit parameters at a different stage than the app expects, more than once, or not at all. Any assumption devs make about how users will interact may be violated.
- Users aren't restricted to using only a web browser. Heaps of tools exist to help someone attack a web application.

The majority of attacks against web apps involve sending input to the server thats crafted to cause some event that wasn't expected, such as:
- Changing the price of a product transmitted in a hidden HTML form field to fraudulently purchase the product for heaps cheaper.
- Modifying a session token in a cookie to hijack another user's session.
- Removing certain params that normally are submitted to exploit a logic flaw in the app's processing.
- Altering some input to inject a malicious DB query and access sensitive data.

## Key Problem Factors
The core security problem is where an app must accept and process untrusted data that may be malicious.

### Underdeveloped Security Awareness
Although awareness of web app security issues has grown in recent years, it's less well-developed than in longer-established areas like networking and operating systems. It's common to meet web devs who don't know that much about security.

### Custom Development
Most web apps are developed in-house by an orgs own staff or 3rd party contractor. Even secure components are customised or bolted together using new code. In this situation, every app is different and may contain its own unique defects. This stands in contrast to a typical infra deployment in which an org purchases a battle hardened product.

### Deceptive Simplicity
With today's app platforms and development tools, it's possible for a novice programmer to create a powerful app in a short period of time. A prominent trend recently has been to use app frameworks that provide ready-made components to handle numerous common areas of functionality that make it quick and easy without fully understanding how they work or the risks they contain.

### Rapidly Evolving Threat Profile
Research into web app hacks and attacks is thriving and new stuff pops up all the time. This means that a team that begins a project with complete knowledge of current threats may have lost this status by the time the app is completed and deployed.

### Resource and Time Constraints
Most app development has strict constraints on time and resources, which often makes it infeasible to employ dedicated security expertise. A quick pen test will often find low hanging fruit, but it may miss more subtle vulnerabilities.

### Overextended Technologies
Much core text, like JS is used in very different context to what it was planned for, which leads to security vulnerabilities as unforeseen side effects emerge.

### Increasing Demands on Functionality
Apps have a lot of functionality, even in a log in page that lets you reset your username, reset your password, use security questions etc that all add to the site's attack surface.

## The New Security Perimeter
The security perimeter of old school apps was often the network perimeter, so securing your network was usually good enough. With web apps, this has shifted so that a big part of the perimeter is within a web app. A single line of defective code can render an org's internal systems vulnerable. A second way in which web apps have moved the security perimeter arises from the threats users themselves face when they access a vulnerable app. A malicious attacker can leverage a benign but vulnerable web app to attack a user.

A further way in which the security perimeter has partly moved to the client side is through the widespread use of e-mail as an extended auth mechanism.
