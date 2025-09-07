---
tags:
  - datatype
search:
  boost: 0.3
---
# `setiterator`

<!--dt-desc-start-->
A setiterator implements a forward iterator over the set type. A forward iterator is an iterator that can only be incremented. Invoking Advance on the iterator will position the iterator on the next element with a value lexicographically greater than the current element. If there is no next element, the iterator will be positioned on the end of the set and IsEnd will be true.
<!--dt-desc-end-->

## Members
<!--dt-members-start-->
### {{ renderMember(type='bool', name='Reset') }}

:   Positions the iterator to the start of the set. True is always returned.

### {{ renderMember(type='bool', name='Advance') }}

:   The iterator is moved to the next item in the set, if one exists. True is returned if the iterator was advanced and False otherwise.

### {{ renderMember(type='bool', name='IsEnd') }}

:   True if the iterator is at the end of the set.

### {{ renderMember(type='string', name='Value') }}

:   Returns the element of the set under the iterator.

<!--dt-members-end-->

## Notes
!!! note

    *   If Advance returns False, IsEnd will be True.
    *   If IsEnd is True, then Value is undefined.

## Examples
<!--dt-examples-start-->
```
Sub SetIteratorTest
    /declare s set

    /echo 'Starting Set Iterator Test'
    /echo 'Count of entries in Set: ${s.Count}'

    | Add entries to the set.
    /echo 'Adding items to the set.

    /if (!${s.Add[A]}) {
        /echo 'Set Add of A failed.'
        /endmacro
    }
    /if (!${s.Add[B]}) {
        /echo 'Set Add of B failed.'
        /endmacro
    }
    /if (!${s.Add[C]}) {
        /echo 'Set Add of C failed.'    
        /endmacro
    }
    /if (!${s.Add[D]}) {
        /echo 'Set Add of D failed.'
        /endmacro
    }
    /if (!${s.Add[E]}) {
        /echo 'Set Add of E failed.'    
        /endmacro
    }

    /declare count int
    /varset count ${s.Count}
    /if (${count} != 5) {
        /echo 'Set count is: ${count} and should be 5.'
        /endmacro
    }

    /echo 'Acquire an iterator to the start of the set.'

    | Get an iterator to the first element and output each
    | element in the set.
    /declare si setiterator
    /vardata si s.First

    /while (!${si.IsEnd}) {
        /echo ${si.Value}
        /if (${si.Advance}) {
            /echo 'Iterator advanced to next element.'
        } else {
            /echo 'Iterator not advanced. IsEnd: ${si.IsEnd}.'
            /endmacro
        }
    }

    | Test Reset and do it again.
    /echo 'Testing Reset.'

    /if (${si.Reset}) {
        /echo 'Iterator Reset.'
    } else {
        /echo 'Iterator could not be reset. IsEnd: ${si.IsEnd}.'
    }

    /while (!${si.IsEnd}) {
        /echo ${si.Value}
        /if (${si.Advance}) {
            /echo 'Iterator advanced to next element.'
        } else {
            /echo 'Iterator not advanced. IsEnd: ${si.IsEnd}.'
            /endmacro
        }
    }

    /echo 'Calling Find[C] on the set.'

    | Acquire an iterator using Find to C.
    /vardata si s.Find[C]

    /while (!${si.IsEnd}) {
        /echo ${si.Value}
        /if (${si.Advance}) {
            /echo 'Iterator advanced to next element.'
        } else {
            /echo 'Iterator not advanced. IsEnd: ${si.IsEnd}.'
            /endmacro
        }
    }

    /echo 'Calling Find[Z] on the set.'

    | Acquire an iterator using Find to Z.
    /vardata si s.Find[Z]

    /if (${si.IsEnd}) {
        /echo 'IsEnd for Find[Z]: ${si.IsEnd}.'
    } else {
        /echo 'IsEnd is FALSE for Find[Z].'
        /endmacro
    }

    /echo 'Ending Set Iterator Test'
    
    /return
```
<!--dt-examples-end-->

<!--dt-linkrefs-start-->
[bool]: ../macroquest/reference/data-types/datatype-bool.md
[string]: ../macroquest/reference/data-types/datatype-string.md
<!--dt-linkrefs-end-->
