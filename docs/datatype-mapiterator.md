---
tags:
  - datatype
search:
  boost: 0.3
---
# `mapiterator`

<!--dt-desc-start-->
A mapiterator implements a forward iterator over the map type. A forward iterator is an iterator that can only be incremented. Invoking Advance on the iterator will position the iterator on the next element with a value lexicographically greater than the current element. If there is no next element, the iterator will be positioned on the end of the map and IsEnd will be true.
<!--dt-desc-end-->

## Members
<!--dt-members-start-->
### {{ renderMember(type='bool', name='Reset') }}

:   Positions the iterator to the start of the map. True is always returned.

### {{ renderMember(type='bool', name='Advance') }}

:   The iterator is moved to the next item in the map, if one exists. True is returned if the iterator was advanced and False otherwise.

### {{ renderMember(type='bool', name='IsEnd') }}

:   True if the iterator is at the end of the map.

### {{ renderMember(type='string', name='Value') }}

:   Returns the element of the map under the iterator.

### {{ renderMember(type='string', name='Key') }}

:   Returns the unique key for the element of the map under the iterator.

### {{ renderMember(type='mapiterator', name='Clone') }}

:   Returns a copy of the current mapiterator. A copy has independent life and initially is over the same element as the source iterator.

<!--dt-members-end-->

## Notes
!!! note

    *   If Advance returns False, IsEnd will be True.
    *   If IsEnd is True, then both Value and Key are undefined.

## Examples
<!--dt-examples-start-->
```
Sub MapIteratorTest
    /declare m map

    /echo 'Starting Map Iterator Test'
    /echo 'Count of entries in Map: ${m.Count}'

    | Add entries to the map.
    /echo 'Adding items to the map.

    /if (!${m.Add[A,One]}) {
        /echo 'Map Add of A failed.'
        /endmacro
    }
    /if (!${m.Add[B,Two]}) {
        /echo 'Map Add of B failed.'
        /endmacro
    }
    /if (!${m.Add[C,Three]}) {
        /echo 'Map Add of C failed.'    
        /endmacro
    }
    /if (!${m.Add[D,Four]}) {
        /echo 'Map Add of D failed.'
        /endmacro
    }
    /if (!${m.Add[E,Five]}) {
        /echo 'Map Add of E failed.'    
        /endmacro
    }

    /declare count int
    /varset count ${m.Count}
    /if (${count} != 5) {
        /echo 'Map count is: ${count} and should be 5.'
        /endmacro
    }

    /echo 'Acquire an iterator to the start of the map.'

    | Get an iterator to the first element and output each
    | element in the map.
    /declare mi mapiterator
    /vardata mi m.First

    /while (!${mi.IsEnd}) {
        /echo ${mi.Key}[${mi.Value}]
        /if (${mi.Advance}) {
            /echo 'Iterator advanced to next element.'
        } else {
            /echo 'Iterator not advanced. IsEnd: ${mi.IsEnd}.'
            /endmacro
        }
    }

    | Test Reset and do it again.
    /echo 'Testing Reset.'

    /if (${mi.Reset}) {
        /echo 'Iterator Reset.'
    } else {
        /echo 'Iterator could not be reset. IsEnd: ${mi.IsEnd}.'
    }

    /while (!${mi.IsEnd}) {
        /echo ${mi.Key}[${mi.Value}]
        /if (${mi.Advance}) {
            /echo 'Iterator advanced to next element.'
        } else {
            /echo 'Iterator not advanced. IsEnd: ${mi.IsEnd}.'
            /endmacro
        }
    }

    /echo 'Calling Find[C] on the map.'

    | Acquire an iterator using Find to C.
    /vardata mi m.Find[C]

    /while (!${mi.IsEnd}) {
        /echo ${mi.Key}[${mi.Value}]
        /if (${mi.Advance}) {
            /echo 'Iterator advanced to next element.'
        } else {
            /echo 'Iterator not advanced. IsEnd: ${mi.IsEnd}.'
            /endmacro
        }
    }

    /echo 'Calling Find[Z] on the map.'

    | Acquire an iterator using Find to Z.
    /vardata mi m.Find[Z]

    /if (${mi.IsEnd}) {
        /echo 'IsEnd for Find[Z]: ${mi.IsEnd}.'
    } else {
        /echo 'IsEnd is FALSE for Find[Z].'
        /endmacro
    }

    /echo 'Ending Map Iterator Test'
    
    /return
```
<!--dt-examples-end-->

<!--dt-linkrefs-start-->
[bool]: ../macroquest/reference/data-types/datatype-bool.md
[mapiterator]: datatype-mapiterator.md
[string]: ../macroquest/reference/data-types/datatype-string.md
<!--dt-linkrefs-end-->
