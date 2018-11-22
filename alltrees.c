#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void intToTree(int tree_num, char *array);
void totext(int c, char *array);
char inttotext(int c);
int texttoint(char c);

int num_of_taxa = 6;




int main(int argc, char *argv[])
    {
    char *tree = NULL;
    int i=0, max = 1;
    
    
    for(i=4; i<=num_of_taxa; i++) max*=((2*i)-5); /* Calculate the number of treesin tree space given the number of taxa */
    tree = malloc(10000*sizeof(char));
    tree[0] = '\0';
    
    for(i=1; i<=max; i++)
        {
        intToTree(i, tree);
        printf("%s\n", tree);
        }    
    
    free(tree);
    
    
    
    
    }
 
    
    
    
    /* this function builds a tree given its number and the number of taxa */
void intToTree(int tree_num, char *array)
    {
    int *path = NULL, i = 0, j=0, k=0, l=0, min = 0, max = 1, oldmin = 0, exit = 0, bracket_count = 0;
    char tmparray[10000], *string= NULL;

    path = malloc((num_of_taxa-3)*sizeof(int));  /* this will store the path of the tree */
    string = malloc(30*sizeof(char));
    
    /************* calculate the path of the tree from a triplet to the full size of the tree ***************/
    
    min = 1;
    for(i=4; i<=num_of_taxa; i++) max*=((2*i)-5);  /* this calculates the total number of possible unrooted trees for the given number of taxa */

 //   printf("path of tree number %d with %d taxa is:\n", tree_num, num_of_taxa);
   
     for(i=4; i<=num_of_taxa; i++)  /* from a triplet to the full complement of taxa, we figure out the placement of each new taxa at each stage */
        {
        
        path[i-4] = div((tree_num - min), ((max - (min - 1))/((2 * i)- 5))).quot + 1;

   //     printf("min = %d, max = %d path = %d\n",min, max, path[i-4]);
       
        if(i != num_of_taxa)
            {
            oldmin = min;
            min = ((path[i-4]-1)*((max - (oldmin - 1))/((2 * i)- 5))) + oldmin;   /* we have to recalculate the min and max values depending on the path previously */
        
            max = ((path[i-4])*((max - (oldmin - 1))/((2 * i)- 5))) + (oldmin -1);
            }
        
        }
    
    
    /**************** next build the tree using the path calculated in the previous section ***************/
    
    /* we start with a triplet */
    strcpy(array, "(1,2,3);");
    
    for(i=4; i<=num_of_taxa; i++)  /* for each taxa to be added */
        {
        /* the path array calculated previously, tells us which object the new taxa is to be paired with. an object can be a set of parenthesis or a taxa */
        j=0; k=0;
        while(j!= path[i-4])
            {
            //printf("%s\n", array);
            exit = 0;
            while(exit == 0)
                {
                switch(array[k])
                    {
                    case '(':
                        break;
                    case ',':
                        break;
                    case ')':
                        j++;
                        exit = 1;
                        break;
                    default:
                        while(array[k+1] != ',' && array[k+1] != '(' && array[k+1] != ')' )
                            {
                            k++;
                            }
                        j++;
                        exit = 1;
                        break;
                    }
                k++;
                }
            } /* the element at position k-1 is the last character of the object the new taxa is to be paired with */
        
        for(j=0; j<k; j++)
            {
            tmparray[j] = array[j]; /* copy in all the elements up to this point into the tmp array */
            }
        
        /* insert the new taxa name preceeded by a comma */
        tmparray[j] = ',';
        tmparray[j+1] = '\0';
        
        string[0] = '\0'; /*initialise the string to hold the name of the taxa */
        totext(i, string);  /* turn the integer name of the taxa into its character equivalent */
        strcat(tmparray, string); /* append the name onto the tree */
        strcat(tmparray, ")" );  /* append on the closing bracket to hold the new pairing */
        
        if(array[j-1] == ')')  /* if we are appending the new taxa to an internal node */
            {
            /* find the end of the string in tmparray */
            k=j;
            while(tmparray[k] != '\0')
                {
                k++;
                }
                
            /* find the position we need to add an open bracket in tmparray */
            l=j;
            bracket_count = 1;
            do
                {
                l--;
                if(tmparray[l] == '(') bracket_count--;
                if(tmparray[l] == ')') bracket_count++;
                }while(bracket_count != 1);

            /* l now is the element in the tmparray we need to add the open bracket */
            /* k is now the last element in the tmparray */
            
            /* move every thing from the end of the string to where we need to add a open bracket forward one space */
            
            for(k=k; k>=l; k--)
                {
                tmparray[k+1] = tmparray[k];
                }
            /* now place the new open bracket in the position of l */
            tmparray[l] = '(';
            }
        else  /* else if we are appending the new taxa to another taxa */
            {
             /* find the end of the string in tmparray */
            k=j;
            while(tmparray[k] != '\0')
                {
                k++;
                }
                
            /* find the position we need to add an open bracket in tmparray */
            l=j;
            while(tmparray[l-1] != ',' && tmparray[l-1] != ')' && tmparray[l-1] != '(')
                {
                l--;
                }
            /* l now is the element in the tmparray we need to add the open bracket */
            /* k is now the last element in the tmparray */
            
            /* move every thing from the end of the string to where we need to add a open bracket forward one space */
            
            for(k=k; k>=l; k--)
                {
                tmparray[k+1] = tmparray[k];
                }
            /* now place the new open bracket in the position of l */
            tmparray[l] = '(';
            
            
            }
        /* now append the rest of the tree onto tmparray */
        /* travel to the end of the tmparray */
        k = j;
        while(tmparray[k] != '\0')
            {
            k++;
            }
        while(array[j] != '\0')
            {
            tmparray[k] = array[j];
            j++;k++;
            }
        tmparray[k] = '\0';
        
        /* copy the new tree onto the main array */
        strcpy(array, tmparray);
            
            
        }
    
    
    
    
    free(path);
    free(string);
    }
    
    
    
void totext(int c, char *array)
    {
    int count = 0, i =0;
    char tmp[30];
    
    if(c != 0)
        {
        while(pow(10, count) <= c)
            {
            tmp[count] = inttotext(fmod(c/pow(10, count), 10));
            count++;
            }
        tmp[count] = '\0';
        array[count] = '\0';
        for(i= count-1; i>=0; i--)
            array[(count-1)- i] = tmp[i];
	}
    else
        {
        array[0] = '0';
        array[1] = '\0';
        }
    }

char inttotext(int c)
    {
   
    	
    switch(c)
        {
        case 1 :
            return('1');
            break;
        case 2 :
            return('2');
            break;
        case 3:
            return('3');
            break;
        case 4:
            return('4');
            break;
        case 5:
            return('5');
            break;
        case 6:
            return('6');
            break;
        case 7:
            return('7');
            break;
        case 8:
            return('8');
            break;
        case 9:
            return('9');
            break;
        default:
            return('0');
            break;
        }
    }



int texttoint(char c)
    {
    switch(c)
        {
        case '1' :
            return(1);
            break;
        case '2' :
            return(2);
            break;
        case '3':
            return(3);
            break;
        case '4':
            return(4);
            break;
        case '5':
            return(5);
            break;
        case '6':
            return(6);
            break;
        case '7':
            return(7);
            break;
        case '8':
            return(8);
            break;
        case '9':
            return(9);
            break;
        default:
            return(0);
            break;
        }
    }

