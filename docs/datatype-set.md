---
tags:
  - datatype
search:
  boost: 0.3
---
# `set`

<!--dt-desc-start-->
A set is a collection of unordered unique values. In practice, the values in this set are ordered lexicographically.

Adding an item that is already in a set does not alter the set.
<!--dt-desc-end-->

## Members
<!--dt-members-start-->
### {{ renderMember(type='int', name='Count') }}

:   Number of items added to the set.

### {{ renderMember(type='bool', name='Clear') }}

:   Removes all items from the set. True is always returned.

### {{ renderMember(type='bool', name='Contains', params='ѕtring') }}

:   True is returned if the item is in the set.

### {{ renderMember(type='bool', name='Add', params='sequence') }}

:   True is returned if the item(s) were added to the set.

### {{ renderMember(type='bool', name='Remove', params='ѕtring') }}

:   True is returned if the item was removed from the set.

### {{ renderMember(type='setiterator', name='First') }}

:   A setiterator is returned on the set where the current element under the iterator is the first element in the set if the set has elements or an empty iterator if the set is empty.

### {{ renderMember(type='setiterator', name='Find', params='ѕtring') }}

:   A setiterator is returned on the set where the current element under the iterator is the item if the item is in the set and an empty iterator if it is not.

<!--dt-members-end-->

## Examples
<!--dt-examples-start-->
```
Sub SetTest
    /declare s set

    /echo 'Starting Set Test'
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
    /if (!${s.Add[C,D,E]}) {
        /echo 'Set Add of C,D,E failed.'    
        /endmacro
    }

    /declare count int
    /varset count ${s.Count}
    /if (${count} != 5) {
        /echo 'Set count is: ${count} and should be 5.'
        /endmacro
    }

    | Now remove A and E.
    /if (!${s.Remove[A]}) {
        /echo 'Remove of A failed.'
        /endmacro
    }
    /if (!${s.Remove[E]}) {
        /echo 'Remove of E failed.'
        /endmacro
    }
    
    /varset count ${s.Count}
    /if (${count} != 3) {
        /echo 'Set count is: ${count} and should be 3.'
        /endmacro
    }

    | Verify that the set contains B, C and D.
    /if (${s.Contains[B]}) {
        /echo 'Set Contains B.'
    } else {
        /echo 'Set does not contain B.'
        /endmacro
    }
    /if (${s.Contains[C]}) {
        /echo 'Set Contains C.'
    } else {
        /echo 'Set does not contain C.'
        /endmacro
    }
    /if (${s.Contains[D]}) {
        /echo 'Set Contains D.'
    } else {
        /echo 'Set does not contain D.'
        /endmacro
    }

    | And verify it does NOT contain A and E.
    /if (${s.Contains[A]}) {
        /echo 'Set should not contain A!'
        /endmacro
    } else {
        /echo 'Set does not contain A.'
    }
    /if (${s.Contains[E]}) {
        /echo 'Set should not contain E!'
        /endmacro
    } else {
        /echo 'Set does not contain E.'
    }

    | Try and Add an element more than once.    
    /if (!${s.Add[B]}) {
        /echo 'Set Add of B failed.'
        /endmacro
    }

    | Adding the same item should not modify the set.
    /varset count ${s.Count}
    /if (${count} != 3) {
        /echo 'Set count is: ${count} and should be 3.'
        /endmacro
    }
    
    | Clear the set. The count should be zero and it
    | should not contain any elements.
    /echo 'Set Clear: ${s.Clear}.'
    /echo 'Set Count: ${s.Count}.'
    
    | And verify it does NOT contain B.
    /if (${s.Contains[B]}) {
        /echo 'Set should not contain B!'
        /endmacro
    } else {
        /echo 'Set does not contain B.'
    }
    
    /echo 'Ending Set Test'
    
    /return
```
<!--dt-examples-end-->

<!--dt-linkrefs-start-->
[bool]: ../macroquest/reference/data-types/datatype-bool.md
[int]: ../macroquest/reference/data-types/datatype-int.md
[setiterator]: datatype-setiterator.md
<!--dt-linkrefs-end-->
