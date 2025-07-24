#include "Contact.hpp"
#include "PhoneBook.hpp"

/* tests */

// 1. empty ADD/SEARCH/EXIT commands - only enter/whitespaces
// 2. ctrl+D during ADD/SEARCH/EXIT commands 
// 3. command other than ADD/SEARCH/EXIT
// 4. SEARCH with empty phone book

// 5. ADD with empty fields
// 6. ctrl+D during waiting for user inputs for ADD fields
// 7. ADD with too long int for number field
// 8. ADD phone number that is not number-only
// 9. ADD with too long first name/last name/nickname - over 10 chars / exactly 10 chars

// 10. SEARCH with index being char/string
// 11. SEARCH with index being out of range
// 12. SEARCH with index being negative number
// 13. SEARCH with index being 0

// 14. SEARCH has proper formatting of fields
// 15. overwriting the oldest contact when adding more than 8 contacts
// 16. overwriting the oldest contact when adding more than 8 contacts again - should overwrite the next one - oldest one

int main()
{
    PhoneBook pb;

    pb.menu();
    return 0;
}
