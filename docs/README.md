# Augmented Library Website

## Github Page Link
https://augmented-library.github.io/Augmented-Library/

## Purpose
Provide a UI for users to view and modify the database. This will also help enforce a schema for the database, as Firebase does not use one. Database schema can be found on the repository's wiki.

**Languages**: HTML, CSS, Javascript\
**Database**: Firebase Cloud Firestore

## File Structure
    docs                # Publishing source for Github Pages
    ├── static          # Static files, in use
    │   ├── scripts     # Javascript, in use
    │   ├── styles      # CSS, in use
    ├── templates       # HTML templates, not in use
    └── ...

## Features
| Item  | Status |
| - | - |
| Read from table on load | Implemented |
| (A) Write to table | Implemented |
| (A) Update HTML table after a write | Implemented |
| User login | Not started |
| Support multiple tables | Not started |
| Input/output sanitization for HTML tables | Started |
| ... | ... |

(A)*: Table will automatically reflect changes made (in most cases)

## Future Plans
Because hosting a website on Github exposes all resources to any visitors, we plan to move off Github and to another web hosting service.

### Considerations
* Heroku

### Other Considerations
* Server: Python, Node.js, Ruby, PHP
* Client: React, Flutter, Vue