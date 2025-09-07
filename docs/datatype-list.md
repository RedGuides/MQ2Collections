---
tags:
  - datatype
search:
  boost: 0.3
---
# `list`

<!--dt-desc-start-->
A sequence of items in which it is possible to remove items from the ends or from arbitrary positions by index. The 'front' of the list is called the Head and the 'rear' the Tail. Items in the list may be indexed by ordinal position, with zero indicating the first item.
<!--dt-desc-end-->

## Members
<!--dt-members-start-->
### {{ renderMember(type='int', name='Count') }}

:   Number of items in the list.

### {{ renderMember(type='bool', name='Clear') }}

:   Removes all elements from the list. Always returns true.

### {{ renderMember(type='bool', name='Contains', params='ѕtring') }}

:   True if at least one instance of string is contained in the list and false otherwise.

### {{ renderMember(type='list', name='Splice') }}

:   Returns a copy of the original list.

### {{ renderMember(type='list', name='Splice', params='іnt') }}

:   Returns a copy of the original list from the indicated position to the end of the list.

### {{ renderMember(type='list', name='Splice', params='int, int') }}

:   Returns a copy of the original list from the position specified by the first argument for an indicated number of elements.

### {{ renderMember(type='int', name='Index', params='ѕtring') }}

:   Returns the ordinal position of String in the List or -1 if String can not be found.

### {{ renderMember(type='string', name='Item', params='іnt') }}

:   Returns the string at the indicated position in the list.

### {{ renderMember(type='bool', name='Insert', params='int,sequence') }}

:   Insert a sequence of comma delimited strings into the source list before the ordinal indicated by Integer. True is returned if the sequence could be inserted and false otherwise.

### {{ renderMember(type='bool', name='Sort') }}

:   Lexicographically orders the items. The source list is modified in place.

### {{ renderMember(type='bool', name='Reverse') }}

:   Reorder the list in such a way that the 0'th item is swapped with the `Count` -1th item, the item with ordinal 1 with the `Count` -2th item, etc.

### {{ renderMember(type='bool', name='Append', params='sequence') }}

:   Insert a sequence of comma delimited strings onto the tail of the list.

### {{ renderMember(type='int', name='Remove', params='ѕtring') }}

:   Remove string from the input list. Return a count of how many times the item was removed.

### {{ renderMember(type='bool', name='Erase', params='іnt') }}

:   Remove an item from the input list by position. Return true if the item was removed or false if not.

### {{ renderMember(type='int', name='Replace', params='string,string') }}

:   Replaces the first string with the second string in the input list. A count of the number of times the replacement was performed is returned.

### {{ renderMember(type='listiterator', name='First') }}

:   A listlterator is returned on the list where the current element under the iterator is the Head of the list if the list has elements or an empty iterator if the list is empty.

### {{ renderMember(type='listiterator', name='Find', params='ѕtring') }}

:   A listiterator is returned on the list where the current element under the iterator is the first item with a value equal to string if string is in the list and an empty iterator if it is not.

### {{ renderMember(type='string', name='Head') }}

:   Remove and return the current item described at position 0 in the list. False is returned if the list is empty.

### {{ renderMember(type='string', name='Tail') }}

:   Remove and return the current item described by position Count -1 in the list. False is returned if the list is empty.

### {{ renderMember(type='int', name='CountOf', params='ѕtring') }}

:   Return a count of the number of times string occurs in the list.

### {{ renderMember(type='string', name='Delimiter', params='ѕtring') }}

:   Sets the delimiter used to separate items in Insert and Append method calls. The previous delimiter is returned.

<!--dt-members-end-->

## Notes
!!! note

    *   Splice returns an empty list if any arguments are invalid.
    *   Splice assumes an origin ordinal of zero. That is, the first position in the list has position zero and the last position is Count - 1.
    *   Splice truncates the returned list if the number of element specified is longer than the input list.
    *   Index will return -1 if Contains return false.
    *   Item assume an origin ordinal of zero. If Item is supplied an argument outside of the range 0 .. Count -1, false will be returned.
    *   Insert will return false if a null sequence of the form 'position,' is inserted.
    *   Insert with a position of zero will insert the sequence before the current head of the list.
    *   Insert with a position equal to Count will be treated as an Append.
    *   Erase assume an origin ordinal of zero. If Erase is supplied an argument outside of the range 0 .. Count -1, false will be returned.

## Examples
<!--dt-examples-start-->
```autoit
Sub ListTest
    /declare l list

    /echo 'Starting List Test'
    /echo 'Count of entries in List: ${l.Count}'

    | Add entries to the list
    /echo 'Adding items to the list.

    /if (${l.Append[One,Two,Three,Four,Five]}) {
    	/echo 'List Append of five items succeeded. Count: ${l.Count}.'
    } else {
    	/echo 'List Append of five items failed.'
	/endmacro
    }

    /declare count int
    /varset count ${l.Count}
    /if (${count} != 5) {
    	/echo 'List count is: ${count} and should be 5.'
	/endmacro
    }

    | Clear the list. The count should be zero.
    /if (${l.Clear}) {
        /echo 'List cleared sucessfully. Count: ${l.Count}.'
    } else {
        /echo 'List clear failed.'
        /endmacro
    }

    /varset count ${l.Count}
    /if (${count} != 0) {
    	/echo 'List count is: ${count} and should be 0.'
	/endmacro
    }

    /echo 'Inserting items into the empty list.'
    | Recreate the list using Insert.
    /if (${l.Insert[0,One,Two,Three,Four,Five]}) {
        /echo 'Insert succeeded. Count: ${l.Count}.'
    } else {
        /echo 'List insertion failed.'
        /endmacro
    }

    /varset count ${l.Count}
    /if (${count} != 5) {
    	/echo 'List count is: ${count} and should be 5.'
	/endmacro
    }

    /echo 'Testing contents of the list for One and Five.'
    | List should contain One and Five
    /if (${l.Contains[One]}) {
        /echo 'List contains One.'
    } else {
        /echo 'Contains of One fails.'
        /endmacro
    }

    /if (${l.Contains[Five]}) {
        /echo 'List contains Five.'
    } else {
        /echo 'Contains of Five fails.'
        /endmacro
    }

    | List should NOT contain Six.
    /if (${l.Contains[Six]}) {
        /echo 'Contains of Six succeeded.'
        /endmacro
    } else {
        /echo 'List does NOT contain Six.'
    }

    /echo 'Testing Index method.'
    /declare index int

    | Index of One should be zero.
    /varset index ${l.Index[One]}
    /if (${index} != 0) {
        /echo 'Index of One is {index} and not 0.'
        /endmacro
    }

    | Index of Three should be two.
    /varset index ${l.Index[Three]}
    /if (${index} != 2) {
        /echo 'Index of Three ${index} and not two.'
        /endmacro
    }

    | Index of Zero should be -1.
    /varset index ${l.Index[Zero]}
    /if (${index} != -1) {
        /echo 'Index of Zero ${index} and not -1.'
        /endmacro
    }

    /echo 'Testinging Item method.'

    | Item of [1] should be Two.
    /if (${l.Item[1].Equal[Two]}) {
        /echo 'Item[1] is: ${l.Item[1]}.'
    } else {
        /echo 'Item[1] should be Two.'
        /endmacro
    }

    /echo 'Testing Splice method.'

    | Copy the list using Splice.
    /declare splice list
    /vardata splice l.Splice

    | Splice length should be five.
    /if (${splice.Count} != 5) {
        /echo 'Length of splice is ${splice.Count} not 5.'
        /endmacro
    } else {
        /echo 'Splice succeeded. Count of spliced list is: ${splice.Count}'
    }

    /echo 'Testing Sort method.'

    | Sort the splice.
    /if (${splice.Sort}) {
        /echo 'Spliced list sorted successfully.'
    } else {
        /echo 'Could not sort the splice.'
        /endmacro
    } 

    | In the sorted list (Five, Four, One, Three, Two), the index
    | of One should be two.
    /if (${splice.Index[One]} == 2) {
        /echo 'Sorted list index of One is: ${splice.Index[One]}.'
    } else {
        /echo 'Index of One in the sorted splice is not two.'
        /endmacro
    }

    | Create another splice from position 2 to the end.
    /vardata splice l.Splice[2]
    /if (${splice.Count} == 3) {
        /echo 'Length of spliced list is: ${splice.Count}.'
    } else {
        /echo 'Length of splice from 2 to the end should be 3.'
        /endmacro
    }

    /echo 'Testing Reverse method.'

    | Reverse the new splice. Should be Five, Four, Three.
    /if (${splice.Reverse}) {
        /echo 'Reverse succeeded. Count is: ${splice.Count}.'
    } else {
        /echo 'Splice could not be reversed.'
        /endmacro
    }

    | First item in reversed splice should be five.
    /if (${splice.Item[0].Equal[Five]}) {
        /echo 'First item in Reverses list is: ${splice.Item[0]}.'
    } else {
        /echo 'Reversed splice first item should be Five.'
        /endmacro
    }

    | Splice using two arguments.
    /vardata splice l.Splice[1, 2]
    /if (${splice.Count} == 2) {
        /echo 'Splice[1, 2] has length ${splice.Count}.'
    } else {
        /echo 'Splice[1, 2] is wrong length. Splice should be length 2 and is ${splice.Count}.'
        /endmacro
    }
    
    /echo 'Testing Remove method.'

    | Remove Three from the list.
    /if (${l.Remove[Three]} == 1) {
        /echo 'Remove of Three succeeded. Contains[Three]: ${l.Contains[Three]}.'
    } else {
        /echo 'Could not remove Three from the list.'
        /endmacro
    }

    /echo 'Testing Erase method.'

    | Erase the second element (Two).
    /if (${l.Erase[1]}) {
        /echo 'Erase by position 1 succeeded. Count: ${l.Count}.'
    } else {
        /echo 'Could not erase the second element from the list.'
        /endmacro
    }

    | The length should now be three.
    /varset count ${l.Count}
    /if (${count} != 3) {
    	/echo 'List count is: ${count} and should be 3.'
	    /endmacro
    }

    /echo 'Testing Replace method.'

    | Replace One with Zero.
    /if (${l.Replace[One,Zero]} != 1) {
        /echo 'One could not be replaced with Zero.'
        /endmacro
    } else {
        /echo 'One replaced with Zero.'
    }

    /echo 'Testing Head and Tail mutators.'

    | Pop off the head and the tail.
    /echo 'Popping off the head: ${l.Head}'
    /echo 'Popping off the tail: ${l.Tail}'

    /echo 'Testing Append method.'

    | Append, One,One,One to the list and count them.
    /if (${l.Append[One,One,One]}) {
        /echo 'Append succeeded. Count: ${l.Count}.'
    } else {
        /echo 'Could not append One to the list three times.'
        /endmacro
    }

    /echo 'Testing CountOf method.'

    | Count how many Ones are in the list. It should be three.
    /if (${l.CountOf[One]} != 3) {
        /echo 'One is not in the list three times.'
        /endmacro
    } else {
        /echo 'CountOf[One] succeeded. CountOf[One]: ${l.CountOf[One]}.'
    }

    /echo 'Ending List Test'
    
    /return
```
<!--dt-examples-end-->

<!--dt-linkrefs-start-->
[bool]: ../macroquest/reference/data-types/datatype-bool.md
[int]: ../macroquest/reference/data-types/datatype-int.md
[list]: datatype-list.md
[listiterator]: datatype-listiterator.md
[string]: ../macroquest/reference/data-types/datatype-string.md
<!--dt-linkrefs-end-->
