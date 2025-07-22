#include "Contact.hpp"
#include "PhoneBook.hpp"

/* tests */

// 1. empty ADD/SEARCH/EXIT commands - only enter/whitespaces
// 2. ctrl+D during ADD/SEARCH/EXIT commands 
// 3. command other than ADD/SEARCH/EXIT
// 4. SEARCH with empty phone book

// 4. ADD with empty fields
// 5. ctrl+D during waiting for user inputs for ADD fields
// 4. ADD with too long int for number field
// 5. ADD phone number that is not number-only
// 6. ADD with too long first name/last name/nickname - over 10 chars / exactly 10 chars

// 7. SEARCH with index being char/string
// 8. SEARCH with index being out of range
// 9. SEARCH with index being negative number
// 10. SEARCH with index being 0

// 11. SEARCH has proper formatting of fields
// 11. overwriting the oldest contact when adding more than 8 contacts
// 11. overwriting the oldest contact when adding more than 8 contacts again - should overwrite the next one - oldest one

int main()
{
    PhoneBook pb;

    pb.menu();
    return 0;
}
