---
tags:
  - datatype
search:
  boost: 0.3
---
# `map`

<!--dt-desc-start-->
A map is a collection of keys, each of which is associated with a value. Maps are also called dictionaries or associative arrays. The keys in a map must be unique. The values may be any arbitrary string.
<!--dt-desc-end-->

## Members
<!--dt-members-start-->
### {{ renderMember(type='int', name='Count') }}

:   Number of items added to the map.

### {{ renderMember(type='bool', name='Clear') }}

:   Removes all items from the map. True is always returned.

### {{ renderMember(type='bool', name='Contains', params='ѕtring') }}

:   True is returned if the item is in the map.

### {{ renderMember(type='bool', name='Add', params='string,string') }}

:   True is returned if the item was added to the map. If the first string, called the 'key' is already in the map, the second string, called the 'value' will be replaced.

### {{ renderMember(type='bool', name='Remove', params='ѕtring') }}

:   True is returned if the 'key' matching string was removed from the map.

### {{ renderMember(type='mapiterator', name='First') }}

:   A mapiterator is returned on the map where the current element under the iterator is the first element in the map if the map has elements or an empty iterator if the map is empty.

### {{ renderMember(type='mapiterator', name='Find', params='ѕtring') }}

:   A mapiterator is returned on the map where the current element under the iterator is the item if the item is in the map and an empty iterator if it is not.

<!--dt-members-end-->

## Examples
<!--dt-examples-start-->
```
Sub MapTest
    /declare m map

    /echo 'Starting Map Test'
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

    | Now remove A and E.
    /if (!${m.Remove[A]}) {
    	/echo 'Remove of A failed.'
    }
    /if (!${m.Remove[E]}) {
    	/echo 'Remove of E failed.'
    }
    
    /varset count ${m.Count}
    /if (${count} != 3) {
    	/echo ' count is: ${count} and should be 3.'
	/endmacro
    }

    | Verify that the map contains B, C and D.
    /if (${m.Contains[B]}) {
    	/echo 'Map Contains B.'
    } else {
    	/echo 'Map does not contain B.'
	/endmacro
    }
    /if (${m.Contains[C]}) {
    	/echo 'Map Contains C.'
    } else {
    	/echo 'Map does not contain C.'
	/endmacro
    }
    /if (${m.Contains[D]}) {
    	/echo 'Map Contains D.'
    } else {
    	/echo 'Map does not contain D.'
	/endmacro
    }

    | And verify it does NOT contain A and E.
    /if (${m.Contains[A]}) {
    	/echo 'Map should not contain A!'
	/endmacro
    } else {
    	/echo 'Map does not contain A.'
    }
    /if (${m.Contains[E]}) {
    	/echo 'Map should not contain E!'
	/endmacro
    } else {
    	/echo 'Map does not contain E.'
    }

    | Adding B again will replace the value associated with B.
    /if (!${m.Add[B,Some new Value]}) {
    	/echo 'Set Add of B failed.'
	/endmacro
    }

    | Adding the same item should not modify the map.
    /varset count ${m.Count}
    /if (${count} != 3) {
    	/echo 'Map count is: ${count} and should be 3.'
	/endmacro
    }
    
    | Clear the map. The count should be zero and it
    | should not contain any elements.
    /echo 'Map Clear: ${m.Clear}.'
    /echo 'Set Count: ${m.Count}.'
    
    | And verify it does NOT contain B.
    /if (${m.Contains[B]}) {
    	/echo 'Map should not contain B!'
	/endmacro
    } else {
    	/echo 'Map does not contain B.'
    }
    
    /echo 'Ending Map Test'
    
    /return
```
<!--dt-examples-end-->

<!--dt-linkrefs-start-->
[bool]: ../macroquest/reference/data-types/datatype-bool.md
[int]: ../macroquest/reference/data-types/datatype-int.md
[mapiterator]: datatype-mapiterator.md
<!--dt-linkrefs-end-->