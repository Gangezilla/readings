# Threat Modeling

Threat modeling is a process by which you can determine what threats are important to an app and find points where defenses may be lacking.

Threat modeling is important to:

- Achieve better coverage in testing to make sure you test all entrypoints
- Find more interesting and valuable bugs to have a testing game plan before you start
- Waste less time on dead ends to eliminate entire classes of vulns before you start.

## Heavy-weight approach

The modeler will document each component and link them. Next you determine threats for each portion of the app, then you rank them by severity. It's difficult to come up with ALL possible threats though. Then you come up with countermeasures.

This is useful for devs and internal teams, but useless for attackers.

## Lightweight approach

- Enumerate entrypoints. Enable burp proxy and use every function for every level you can find
- Document target assets: Think through and write down every asset in which an attacker may be interested. User PII and passwords, admin panel access, transaction histories, source code, database credentials.
- Develop game plan: Rank entrypoints in order of perceived value. For example, an entrypoint which takes little to no user data is less valuable than one which takes a substantial amount of data. Additionally, you have enough info to eliminate entire vulnerability classes from your tests.

This shouldn't take much more than an hour. If you take heaps longer than this, maybe re-evaluate what you're doing. The more often you do this the easier it'll be.