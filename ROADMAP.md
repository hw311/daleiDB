# daleiDB Development Roadmap
_Last Modified: Mon, Dec 17 2018 23:11:34 PST_

This document describes the general idea, the current status, and future todo-
list and milestones of this project for contributors.

### Project scope
_daleiDB_ is a simple relational database management system developed with
learning purposes. The layerd architecture of a typical DBMS is adopted. Main
proposed components of daleiDB include:

- Interfaces
  - Programming APIs
  - CLI
- Query language (SQL)
  - Query parser
- Query optimization and execution
  - Query optimizer
  - Plan executor
  - Relational operators
- Files and access methods
  - File manager
  - Index manager
  - Catalog
- Buffer management
- Disk space and I/O management

In the future, daleiDB may also implement distributed features and transaction management.

### Current status
The project has just started and is still in the designing phase.

### TODO list and future milestones
In constructing daleiDB from scratch, this project takes a bottom-up approach.
Detailed TODO lists will be updated once the system design is completed.

- Project metas
  - [x] Roadmap
  - [ ] System design
  - [ ] Documentations
- Components and functionalities
  - [ ] Disk space and I/O management
  - [ ] Buffer management
  - [ ] Files and access methods
  - [ ] Query optimization and execution
  - [ ] Query language
  - [ ] Interfaces
