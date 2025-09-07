---
tags:
  - datatype
search:
  boost: 0.3
---
# `listiterator`

<!--dt-desc-start-->
A listiterator implements a forward iterator over the list type. A forward iterator is an iterator that can only be incremented. Invoking Advance on the iterator will position the iterator on the next element in the list. Elements in a list are identified by position. The positions have ordinals in the range 0 to Count -1. If there is no next element, the iterator will be positioned on the end of the list and IsEnd will be true.
<!--dt-desc-end-->

## Members
<!--dt-members-start-->
### {{ renderMember(type='bool', name='Reset') }}

:   Positions the iterator to the start of the list. True is always returned.

### {{ renderMember(type='bool', name='Advance') }}

:   The iterator is moved to the next item in the list, if one exists. True is returned if the iterator was advanced and False otherwise.

### {{ renderMember(type='bool', name='IsEnd') }}

:   True if the iterator is at the end of the list.

### {{ renderMember(type='string', name='Value') }}

:   Returns the element of the list under the iterator.

### {{ renderMember(type='listiterator', name='Clone') }}

:   Returns a copy of the current listiterator. A copy has independent life and initially is over the same element as the source iterator.

<!--dt-members-end-->

## Notes
!!! note

    *   If Advance returns False, IsEnd will be True.
    *   If IsEnd is True, then Value is undefined.


## Examples
<!--dt-examples-start-->
```
Sub ListIteratorTest
    /declare l list

    /echo 'Starting List Iterator Test'
    /echo 'Count of entries in List: ${l.Count}'

    | Add entries to the list.
    /echo 'Adding items to the list.

    /if (!${l.Append[One,Two,Three,Four,Five]}) {
        /echo 'List append failed.'
        /endmacro
    }

    /declare count int
    /varset count ${l.Count}
    /if (${count} != 5) {
        /echo 'List count is: ${count} and should be 5.'
        /endmacro
    }

    /echo 'Acquire an iterator to the start of the list.'

    | Get an iterator to the first element and output each
    | element in the list.
    /declare li listiterator
    /vardata li l.First

    /while (!${li.IsEnd}) {
        /echo ${li.Value}
        /if (${li.Advance}) {
            /echo 'Iterator advanced to next element.'
        } else {
            /echo 'Iterator not advanced. IsEnd: ${li.IsEnd}.'
            /endmacro
        }
    }

    | Test Reset and do it again.
    /echo 'Testing Reset.'

    /if (${li.Reset}) {
        /echo 'Iterator Reset.'
    } else {
        /echo 'Iterator could not be reset. IsEnd: ${li.IsEnd}.'
    }

    /while (!${li.IsEnd}) {
        /echo ${li.Value}
        /if (${li.Advance}) {
            /echo 'Iterator advanced to next element.'
        } else {
            /echo 'Iterator not advanced. IsEnd: ${li.IsEnd}.'
            /endmacro
        }
    }

    /echo 'Calling Find[Three] on the list.'

    | Acquire an iterator using Find to Three
    /vardata li l.Find[Three]

    /echo 'After Find[Three]: IsEnd: ${li.IsEnd}.'

    /while (!${li.IsEnd}) {
        /echo ${li.Value}
        /if (${li.Advance}) {
            /echo 'Iterator advanced to next element.'
        } else {
            /echo 'Iterator not advanced. IsEnd: ${li.IsEnd}.'
            /endmacro
        }
    }

    /echo 'Calling Find[Z] on the list.'

    | Acquire an iterator using Find to Z.
    /vardata li l.Find[Z]

    /if (${li.IsEnd}) {
        /echo 'IsEnd for Find[Z]: ${li.IsEnd}.'
    } else {
        /echo 'IsEnd is FALSE for Find[Z].'
        /endmacro
    }

    /echo 'Ending List Iterator Test'
    
    /return
```
<!--dt-examples-end-->

<!--dt-linkrefs-start-->
[bool]: ../macroquest/reference/data-types/datatype-bool.md
[listiterator]: datatype-listiterator.md
[string]: ../macroquest/reference/data-types/datatype-string.md
<!--dt-linkrefs-end-->