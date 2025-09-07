---
tags:
  - plugin
resource_link: "https://www.redguides.com/community/resources/mq2collections.1107/"
support_link: "https://www.redguides.com/community/threads/mq2collections.69099/"
repository: "https://github.com/RedGuides/MQ2Collections"
authors: "TypePun"
tagline: "Collection types for MQ -- useful for scripts to create stacks, queues, maps, lists."
quick_start: "https://github.com/TypePun/MQ2Collections/wiki"
search:
  boost: 0.3
---

# MQ2Collections

<!--desc-start-->
MQ2Collections is a Macroquest plugin. The plugin creates a number of collection types for scripts. Out of the box MQ supports one collection: the array. Collection types enable script writers to use data structures that more naturally pair with the algorithm they are implementing. For example, if a script writer is implementing a first-in first-out structure for casting buffs, then a queue would be an appropriate structure. On the other hand, if he or she is maintaining a set of IDs representing mobs pulled to camp, then a set or list would be the natural mechanism.
<!--desc-end-->

#### Why did I write it?

My motivation in writing this plugin was to expose more powerful and natural data structuring tools to script writers. With these tools, script writers will be able to express solutions that solve the problem they want to solve rather than organizing data and building data structures.

#### What types are available?

The current release makes available the following data structures: the stack, set, list, queue and map. Iterators over the set, list and map are also provided. For those familiar with the C++ Standard Template Library (STL), the types and their semantics should seem natural. If they do not, please let me know by email at: typepun08@outlook.com.

#### Limitations

At present, the collections hold strings. That is, if you want to store an integer, floating point value or an object, you have to first convert it (or serialize it) as a string.

#### Official Documentation

Extensive documentation and manuals can be found here:
[github](https://github.com/TypePun/MQ2Collections/wiki)

## Top-Level Objects

## [list](tlo-list.md)
{% include-markdown "projects/mq2collections/tlo-list.md" start="<!--tlo-desc-start-->" end="<!--tlo-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/tlo-list.md') }}

## [listiterator](tlo-listiterator.md)
{% include-markdown "projects/mq2collections/tlo-listiterator.md" start="<!--tlo-desc-start-->" end="<!--tlo-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/tlo-listiterator.md') }}

## [map](tlo-map.md)
{% include-markdown "projects/mq2collections/tlo-map.md" start="<!--tlo-desc-start-->" end="<!--tlo-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/tlo-map.md') }}

## [mapiterator](tlo-mapiterator.md)
{% include-markdown "projects/mq2collections/tlo-mapiterator.md" start="<!--tlo-desc-start-->" end="<!--tlo-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/tlo-mapiterator.md') }}

## [queue](tlo-queue.md)
{% include-markdown "projects/mq2collections/tlo-queue.md" start="<!--tlo-desc-start-->" end="<!--tlo-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/tlo-queue.md') }}

## [set](tlo-set.md)
{% include-markdown "projects/mq2collections/tlo-set.md" start="<!--tlo-desc-start-->" end="<!--tlo-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/tlo-set.md') }}

## [setiterator](tlo-setiterator.md)
{% include-markdown "projects/mq2collections/tlo-setiterator.md" start="<!--tlo-desc-start-->" end="<!--tlo-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/tlo-setiterator.md') }}

## [stack](tlo-stack.md)
{% include-markdown "projects/mq2collections/tlo-stack.md" start="<!--tlo-desc-start-->" end="<!--tlo-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/tlo-stack.md') }}

## DataTypes

## [list](datatype-list.md)
{% include-markdown "projects/mq2collections/datatype-list.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/datatype-list.md') }}

<h2>Members</h2>
{% include-markdown "projects/mq2collections/datatype-list.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
{% include-markdown "projects/mq2collections/datatype-list.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}

## [listiterator](datatype-listiterator.md)
{% include-markdown "projects/mq2collections/datatype-listiterator.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/datatype-listiterator.md') }}

<h2>Members</h2>
{% include-markdown "projects/mq2collections/datatype-listiterator.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
{% include-markdown "projects/mq2collections/datatype-listiterator.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}

## [map](datatype-map.md)
{% include-markdown "projects/mq2collections/datatype-map.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/datatype-map.md') }}

<h2>Members</h2>
{% include-markdown "projects/mq2collections/datatype-map.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
{% include-markdown "projects/mq2collections/datatype-map.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}

## [mapiterator](datatype-mapiterator.md)
{% include-markdown "projects/mq2collections/datatype-mapiterator.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/datatype-mapiterator.md') }}

<h2>Members</h2>
{% include-markdown "projects/mq2collections/datatype-mapiterator.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
{% include-markdown "projects/mq2collections/datatype-mapiterator.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}

## [queue](datatype-queue.md)
{% include-markdown "projects/mq2collections/datatype-queue.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/datatype-queue.md') }}

<h2>Members</h2>
{% include-markdown "projects/mq2collections/datatype-queue.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
{% include-markdown "projects/mq2collections/datatype-queue.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}

## [set](datatype-set.md)
{% include-markdown "projects/mq2collections/datatype-set.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/datatype-set.md') }}

<h2>Members</h2>
{% include-markdown "projects/mq2collections/datatype-set.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
{% include-markdown "projects/mq2collections/datatype-set.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}

## [setiterator](datatype-setiterator.md)
{% include-markdown "projects/mq2collections/datatype-setiterator.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/datatype-setiterator.md') }}

<h2>Members</h2>
{% include-markdown "projects/mq2collections/datatype-setiterator.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
{% include-markdown "projects/mq2collections/datatype-setiterator.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}

## [stack](datatype-stack.md)
{% include-markdown "projects/mq2collections/datatype-stack.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2collections/datatype-stack.md') }}

<h2>Members</h2>
{% include-markdown "projects/mq2collections/datatype-stack.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
{% include-markdown "projects/mq2collections/datatype-stack.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}
