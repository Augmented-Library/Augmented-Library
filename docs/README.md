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
| Write to table | Implemented |
| Update HTML table after a write (static) | Implemented but subject to change to refresh page after write |
| User login | Not started |
| Support multiple tables | Not started |
| Input/output sanitization for HTML tables | Not started |
| ... | ... |