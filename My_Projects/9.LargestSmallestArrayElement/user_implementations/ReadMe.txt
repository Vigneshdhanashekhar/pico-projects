logic to  find the greatest and smallest elements of a array.
eg  arr1=[2,4,1,5,7,3]
min=arr1[0]
max=arr1[0]
for (i =0;i<sizeof(arr1);i++){
    if max<arr1[i]{
        max=arr1[i];
    }
    if min<arr1[i]{
        max=arr1[i];
    }
    return(max,min);
}