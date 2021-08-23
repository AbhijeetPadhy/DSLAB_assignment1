Instructions to run the code
----------------------------

1. Install Graphwiz from the below link:
	https://graphviz.org/download/
2. Please remember to add its path to environemt variable during installation.
3. Compile the main.cpp file. In Linux use the below command to compile:
	g++ main.cpp
4. Execute the executable produced from above step. In Linux use the below command to execute:
	./a.out
5. You will be shown the below prompt upon execution:

								This is an implementation of Threaded Binary Search Tree
								--------------------------------------------------------
								1. Insert an element
								2. Delete an element
								3. Search for an element
								4. Print Inorder Traversal
								5. Print Reverse Inorder Traversal
								6. Print successor
								7. Split a copy of the tree into two halves
								8. Find elements within a particular range
								9. Find the k-th Largest element
								10.Print an image of the tree
								11.Insert a series of elements
								Press 0 to quit.
								Enter Your Choice:

6. Enter the appropriate choice to do any operation.
7. A lot of examples are provided in the "Test Cases" section on how to operate each choice.
8. If we select option 10, which is used to split a tree, a file named graph.gv will be created in the same directory of the executable. 
	To convert it to a png image, we have to run the below command in the same directory:

	dot -Tpng graph.gv -o graph.png
	
	This command converts the file named graph.gv to graph.png. Open the image file to see a pictorial representation of the tree.

9. If we select the option 7, we are asked of a value around which we have to split the tree. On entering the value, a new tree is 
	cloned which is then splitted and the inorder traversals of both the trees are printed. In addition to this, two .gv files 
	are created called left.gv and right.gv. These are the graphviz files for the two trees. Convert both the files to their 
	respective png images using the below commands:
	
	dot -Tpng left.gv -o left.png
	dot -Tpng right.gv -o right.png
	
	Thus two files left.png and right.png are created.
10. If we have to insert a single element, we can choose option 1. But if we have to insert a lot of elements in a sequence, we have
	to choose option 11.
11. To delete an element choose option 2. 
13. Tosearch for an element choose option 3.
14. To print inorder or reverse inorder traversal of tree, choose option 4 or 5 respectively.
15. To print successor of an element choose option 6.
16. To find elements in a particular range choose option 8 and then specify the range.
17. To find the kth largest element choose option 9.
18. To quit, choose option 0. 
