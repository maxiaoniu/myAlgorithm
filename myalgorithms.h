#ifndef MYALGORITHMS_H
#define MYALGORITHMS_H
#include <utility>
class myAlgorithms
{
public:
    myAlgorithms();
    ~myAlgorithms();

    template<typename T> T max(const T a, const T b) const
    {return a>b?a:b; }
    template<typename T> T min(const T a, const T b) const
    {return a<b?a:b; }

    template<typename InputIterator1,
             typename InputIterator2>
    std::pair<InputIterator1,
              InputIterator2> mismatch(InputIterator1 beg,
                                       InputIterator1 end,
                                       InputIterator2 cmpBeg);
    //Sorted-Range Algorithms - Merge Element
    //set union
    //must be sorted
    template<typename InputIterator1,
             typename InputIterator2,
             typename OutputIterator>
    OutputIterator set_union(InputIterator1 beg1, InputIterator1 end1,
              InputIterator2 beg2, InputIterator2 end2,
              OutputIterator result);
    //set intersection
    //must be sorted
    template<typename InputIterator1,
             typename InputIterator2,
             typename OutputIterator>
    OutputIterator set_intersection(InputIterator1 beg1, InputIterator1 end1,
              InputIterator2 beg2, InputIterator2 end2,
              OutputIterator result);
    //set difference
    //must be sorted
    template<typename InputIterator1,
             typename InputIterator2,
             typename OutputIterator>
    OutputIterator set_difference(InputIterator1 beg1, InputIterator1 end1,
              InputIterator2 beg2, InputIterator2 end2,
              OutputIterator result);

    //set symmetric difference
    //must be sorted
    template<typename InputIterator1,
             typename InputIterator2,
             typename OutputIterator>
    OutputIterator set_symmetric_difference(InputIterator1 beg1, InputIterator1 end1,
              InputIterator2 beg2, InputIterator2 end2,
              OutputIterator result);

    //adjacent find
    //return the first element in the range [beg,end) that has a value equal to the value of the following
    //element
    template<typename ForwardIterator>
    ForwardIterator adjacent_find(ForwardIterator beg, ForwardIterator end);

    //search element
    //find_first_of
    //returns the position of the first element in the range [beg,end) that is also in the range
    //[SearchBeg, SearchEnd).
    template<typename InputIterator, typename ForwardIterator>
    InputIterator find_first_of(InputIterator beg, InputIterator end,
                                ForwardIterator searchBeg, ForwardIterator searchEnd);

};

template<typename InputIterator1, typename InputIterator2>
std::pair<InputIterator1, InputIterator2> myAlgorithms::mismatch(InputIterator1 beg,
                                                   InputIterator1 end,
                                                   InputIterator2 cmpBeg)
{
    while(beg != end && *beg == *cmpBeg)
    {
        ++beg;
        ++cmpBeg;
    }
    return std::pair<InputIterator1, InputIterator2>(beg,cmpBeg);
}

template<typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator>
OutputIterator myAlgorithms::set_union(InputIterator1 beg1, InputIterator1 end1,
          InputIterator2 beg2, InputIterator2 end2,
          OutputIterator result)
{
    //when two range all arrive end
    while(beg1 != end1 && beg2 != end2)
    {
        //the basic idea is compare each element, one by one,
        // sorted the two sets and delete the same element!

        if(*beg1 < *beg2)
        {
            *result = *beg1;
            ++beg1;
        }
        else if(*beg1 > *beg2)
        {
            *result = *beg2;
            ++beg2;
        }
        else
        {
            //*beg1==*beg2, select one of them
            *result = *beg1;
            ++beg1;
            ++beg2;
        }
        ++result;

    }
    //must deal with the last elements
    //using copy() function to increas the efficency
    return copy(beg2,end2,copy(beg1,end1,result));
}

template<typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator>
OutputIterator myAlgorithms::set_intersection(InputIterator1 beg1, InputIterator1 end1,
          InputIterator2 beg2, InputIterator2 end2,
          OutputIterator result)
{
    //when two range all arrive end
    while(beg1 != end1 && beg2 != end2)
    {
        //the basic idea is compare each element, one by one,
        // sorted the two sets and delete the same element!

        if(*beg1 < *beg2)
        {
            ++beg1;
        }
        else if(*beg1 > *beg2)
        {
            ++beg2;
        }
        else
        {
            //*beg1==*beg2, select one of them
            *result = *beg1;
            ++beg1;
            ++beg2;
            ++result;
        }

    }
    return result;
}
template<typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator>
OutputIterator myAlgorithms::set_difference(InputIterator1 beg1, InputIterator1 end1,
          InputIterator2 beg2, InputIterator2 end2,
          OutputIterator result)
{
    //when two range all arrive end
    while(beg1 != end1 && beg2 != end2)
    {
        //the basic idea is compare each element, one by one,
        // sorted the two sets and delete the same element!

        if(*beg1 < *beg2)
        {
            *result = *beg1;
            ++beg1;
            ++result;
        }
        else if(*beg1 > *beg2)
        {
            ++beg2;
        }
        else
        {
            //*beg1==*beg2, select one of them
            ++beg1;
            ++beg2;
        }

    }
    //copy the last elements in s1
    return copy(beg1,end1,result);
}


//set symmetric difference
//must be sorted
template<typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator>
OutputIterator myAlgorithms::set_symmetric_difference(InputIterator1 beg1, InputIterator1 end1,
          InputIterator2 beg2, InputIterator2 end2,
          OutputIterator result)
{
    //when two range all arrive end
    while(beg1 != end1 && beg2 != end2)
    {
        //the basic idea is compare each element, one by one,
        // sorted the two sets and delete the same element!

        if(*beg1 < *beg2)
        {
            *result = *beg1;
            ++beg1;
            ++result;
        }
        else if(*beg1 > *beg2)
        {
            *result = *beg2;
            ++beg2;
            ++result;
        }
        else
        {
            //*beg1==*beg2, select one of them
            ++beg1;
            ++beg2;
        }

    }
    //copy the last elements in s1
    return copy(beg1,end1,result);
}

template<typename ForwardIterator>
ForwardIterator myAlgorithms::adjacent_find(ForwardIterator beg, ForwardIterator end)
{
    if(beg == end)
        return end;
    ForwardIterator next = beg;
    while(++next != end)
    {
        if(*beg == *next)
        {
            return beg;
        }
        beg = next;
    }
    return end;
}
template<typename InputIterator, typename ForwardIterator>
InputIterator myAlgorithms::find_first_of(InputIterator beg, InputIterator end,
                            ForwardIterator searchBeg, ForwardIterator searchEnd)
{
    for(; beg != end; beg++)
    {
        for(ForwardIterator s = searchBeg; s != searchEnd; s++)
        {
            if(*beg == *s)
                return beg;
        }
    }
    return end;
}
#endif // MYALGORITHMS_H
