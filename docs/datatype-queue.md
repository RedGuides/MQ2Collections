---
tags:
  - datatype
search:
  boost: 0.3
---
# `queue`

<!--dt-desc-start-->
A queue is a first-in, first-out data structure. Items Pushed are inserted at the rear, or 'tail' of the queue. Items removed, or Popped are taken from the 'front' of the queue.
<!--dt-desc-end-->

## Members
<!--dt-members-start-->
### {{ renderMember(type='int', name='Count') }}

:   Number of items inserted onto the queue.

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
    *   Peek retrieves the oldest element Pushed onto the queue. Count is not modified by calling Peek.


## Examples
<!--dt-examples-start-->
```
Sub QueueTest
    /declare q queue

    /echo 'Starting Queue Test'
    /echo 'Queue is Empty: ${q.IsEmpty}'
    
    | Push entries on the queue and pop them off.
    | Note: entries are inserted (Pushed) in and removed
    | (Popped) in the same order. That is, Pushing A, B, C, D, E
    | and then Popping them will return A, B, C, D, E.
    /echo 'Pushing items onto the Queue.'

    /if (!${q.Push[A]}) {
    	/echo 'Queue Push of A failed.'
	/endmacro
    }
    /if (!${q.Push[B]}) {
    	/echo 'Queue Push of B failed.'
	/endmacro
    }
    /if (!${q.Push[C]}) {
    	/echo 'Queue Push of C failed.'
	/endmacro
    }
    /if (!${q.Push[D]}) {
    	/echo 'Queue Push of D failed.'
	/endmacro
    }
    /if (!${q.Push[E]}) {
    	/echo 'Queue Push of E failed.'
	/endmacro
    }

    /declare count int
    /varset count ${q.Count}
    /if (${count} != 5) {
    	/echo 'Queue count is: ${count} and should be 5.'
	/endmacro
    }

    /echo 'Queue is Empty: ${q.IsEmpty}'
    
    | Peek at the front item:
    /echo 'Front item is: ${q.Peek}'
    
    | Pop items off the queue.

    /echo 'Popping item off queue: ${q.Pop}'
    /echo 'Popping item off queue: ${q.Pop}'
    /echo 'Popping item off queue: ${q.Pop}'
    /echo 'Popping item off queue: ${q.Pop}'
    /echo 'Popping item off queue: ${q.Pop}'

    /echo 'Queue is Empty: ${q.IsEmpty}'
    /echo 'Ending Queue Test'
    
    /return
```
<!--dt-examples-end-->

<!--dt-linkrefs-start-->
[bool]: ../macroquest/reference/data-types/datatype-bool.md
[int]: ../macroquest/reference/data-types/datatype-int.md
[string]: ../macroquest/reference/data-types/datatype-string.md
<!--dt-linkrefs-end-->
