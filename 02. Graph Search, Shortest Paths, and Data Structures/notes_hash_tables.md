# Hash Tables
Hash tables maintain a possibly evolving set of data - transactions, people with associated data, IP addresses, etc. They support three core operations:
-   **Insert**: Add new record using a key.
-   **Delete**: Delete existing record.
-   **Lookup**: Check for a particular record.
All operations run in  **O(1) time**  when <u> properly implemented </u> on <u> non-pathological data.</u>
### Applications
* De-Duplication : Remove duplicates (keep track of unique objects) in a stream of data.
* The 2 Sum Problem : 
	* To determine whether there are two integers x, y in array A such that x + y = t.
	* Insert elements x in a hash table (O(n)) and then for each x in A, look up t - x.
### High-Level Design Concept
1.  **Setup**: Define universe U (e.g., all IP addresses, all names, all chessboard configurations) - generally REALLY BIG.
2.  **Goal**: Maintain evolving set S ⊆ U - generally of reasonable size.
3.  **Solution**:
    -   Pick n buckets (assume |S| doesn't vary much).
    -   Choose hash function h: U → {0,1,2,...,n-1}.
    -   Use array A of length n, store x in A[h(x)].
### Collision Resolution Strategies
When distinct elements x, y ∈ U satisfy h(x) = h(y), we have a collision (Two different keys x, y in same bucket h(x)). Two main approaches exist:
**Solution 1: Separate Chaining**
&rarr; Allow multiple items in each bucket by using a linked list.
-   Each bucket A[i] contains a linked list.
-   When collision occurs, just add the new item to the list.
-   To find an item, go to the right bucket and search through its list.

**Solution 2: Open Addressing**
&rarr; Only one item per bucket. If your spot is taken, find another empty spot using a systematic search.
-   Each bucket holds exactly one item (or is empty).
-   When collision occurs, use a "probe sequence" to find the next available bucket.
-   Keep trying locations until you find an empty spot.
	- Common Probe Sequences : 
		- Linear Probing &rarr; Look Consecutively (+1 steps).
		- Double hashing : Use a second hash function to determine step size.

### Performance Analysis with Chaining
&rarr; While Insert is always O(1) in chaining (just add to front of list), the performance of Lookup and Delete depends heavily on list lengths.
**The Performance Range**:
-   **Best Case**: All lists have equal length m/n (where m = total objects, n = number of buckets).
-   **Worst Case**: All m objects end up in the same bucket, creating one list of length m.
- **Range**: Could be anywhere between m/n and n.

**Critical Point**: Performance depends entirely on how well hash function distributes data. For example : 
-   **Bad hash function**: All keys hash to same bucket → O(m) operations (like a linked list).
-   **Good hash function**: Keys spread evenly → O(m/n) = O(1) operations (if load factor α = m/n is constant).

###  Properties of a "Good" Hash Function
**Property 1: Should Lead to Good Performance**
&rarr; Spread data out evenly across all buckets.
    
-   **Gold Standard** &rarr;  Completely random hashing
    -   Each key has equal probability of mapping to any bucket.
    -   Minimizes clustering and long chains.
    -   Theoretical ideal (though not practically implementable).

**Property 2: Should Be Easy to Store/Very Fast to Evaluate**
-   **Storage**: Hash function shouldn't require excessive memory.
-   **Speed**: Computing h(x) should be very fast (constant time).
-   **Practicality**: Simple arithmetic operations preferred over complex computations.

### The load of a hash table
&rarr; &alpha; = $\frac{\text{number of objects in hash table}}{\text{number of buckets in hash table}}$
&rarr; With Open Addressing, need &alpha; << 1.

---
&Star; No hash function can work well for all possible data sets. An adversary can always find inputs that cause everything to collide in the same bucket, degrading performance from O(1) to O(n).
**Solution 1:** Cryptographic Hash Functions
&rarr;  Use cryptographically secure hash functions like SHA-2, SHA-256, etc.
&rarr; Infeasible to reverse engineer a pathological data set.
&rarr; Trade-offs :
-   ✅ Security against adversarial attacks.
-   ❌ Computationally expensive (SHA-2 is much slower than simple hash functions).
-   ❌ Overkill for most applications.

**Solution 2:**  Randomization (Universal Hashing)
&rarr; Use a  **family H of hash functions**  rather than a single fixed function.
&rarr; "Almost all" functions h ∈ H spread any data set S out "pretty evenly".
**The Randomization Strategy**:
1.  Design a family H of many different hash functions.
2.  At runtime, randomly choose one function h from H.
3.  Use h for all hash table operations.

**Why This Works**:
-   While each individual hash function in H has some pathological data sets.
-   For any fixed data set S, only a small fraction of functions in H perform poorly on S.
-   Random selection makes bad performance unlikely.
---
## Bloom Filters
&rarr; Bloom filters represent an elegant extension of hash table concepts that trades perfect accuracy for remarkable space efficiency.
**Key Characteristics**:
-   **No false negatives**: If a bloom filter says an element is NOT in the set, it's definitely not there.
-   **Possible false positives**: If it says an element IS in the set, it might be wrong.
-   **Space efficient**: Requires only about 9.6 bits per element for 1% error rate, regardless of element size.
-   **Fast operations**: Constant time O(1) insertions and lookups.

**Supported Operations**:
-   **Insert**: Add new elements to the set.
-   **Lookup**: Check if element might be in the set.
-   **No deletions**: Cannot remove elements once added.
