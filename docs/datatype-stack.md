---
tags:
  - datatype
search:
  boost: 0.3
---
# `stack`

<!--dt-desc-start-->
A stack is a last-in, first-out data structure. Items inserted (Pushed) are placed on the 'top' of the queue. Items removed (Popped) are also removed from the 'top'.
<!--dt-desc-end-->

## Members
<!--dt-members-start-->
### {{ renderMember(type='int', name='Count') }}

:   Number of items inserted onto the stack.

### {{ renderMember(type='bool', name='Push', params='ѕtring') }}

:   True if the item was pushed successfully.

### {{ renderMember(type='string', name='Pop') }}

:   False is returned if IsEmpty is true.

### {{ renderMember(type='bool', name='IsEmpty') }}

:   True if Count = 0, False otherwise.

### {{ renderMember(type='string', name='Peek') }}

:   False is returned if IsEmpty is true.

<!--dt-members-end-->

## Notes
!!! note

    *   Pop decreases Count by 1 unless IsEmpty is true.
    *   Push increases Count by 1. IsEmpty will never be true after calling Push.
    *   Peek retrieves the last element Pushed onto the stack. Count is not modified by calling Peek.




## Examples
<!--dt-examples-start-->
```
Sub StackTest
    /declare s stack

    /echo 'Starting Stack Test'
    /echo 'Stack is Empty: ${s.IsEmpty}'
    
    | Push entries on the stack and pop them off.
    | Note: entries are inserted (Pushed) in and removed
    | (Popped) in reverse order. That is, Pushing A, B, C, D, E
    | and then Popping them will return E, D, C, D, A.

    /echo 'Pushing items onto the Stack.'
    /if (!${s.Push[A]}) {
    	/echo 'Stack Push of A failed.'
	/endmacro
    }
    /if (!${s.Push[B]}) {
    	/echo 'Stack Push of B failed.'
	/endmacro
    }
    /if (!${s.Push[C]}) {
    	/echo 'Stack Push of C failed.'
	/endmacro
    }
    /if (!${s.Push[D]}) {
    	/echo 'Stack Push of D failed.'
	/endmacro
    }
    /if (!${s.Push[E]}) {
    	/echo 'Stack Push of E failed.'
	/endmacro
    }

    /declare count int
    /varset count ${s.Count}
    /if (${count} != 5) {
    	/echo 'Stack count is: ${count} and should be 5.'
	/endmacro
    }

    /echo 'Stack is Empty: ${s.IsEmpty}'
    
    | Peek at the top item:
    /echo 'Top item is: ${s.Peek}'
    
    | Pop items off the stack.

    /echo 'Popping item off stack: ${s.Pop}'
    /echo 'Popping item off stack: ${s.Pop}'
    /echo 'Popping item off stack: ${s.Pop}'
    /echo 'Popping item off stack: ${s.Pop}'
    /echo 'Popping item off stack: ${s.Pop}'

    /echo 'Stack is Empty: ${s.IsEmpty}'
    /echo 'Ending Stack Test'
    
    /return
```
<!--dt-examples-end-->

<!--dt-linkrefs-start-->
[bool]: ../macroquest/reference/data-types/datatype-bool.md
[int]: ../macroquest/reference/data-types/datatype-int.md
[string]: ../macroquest/reference/data-types/datatype-string.md
<!--dt-linkrefs-end-->
