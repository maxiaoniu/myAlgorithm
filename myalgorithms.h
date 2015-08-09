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

    //search element
    //search first subrange
    //return the position of the first element of the first subrange matching the range [beg,end)
    //in the range [searchBeg, searchEnd)
    template<typename ForwardIterator1, typename ForwardIterator2>
    ForwardIterator1 search(ForwardIterator1 beg, ForwardIterator1 end,
                            ForwardIterator2 searchBeg, ForwardIterator2 searchEnd)
    {
        int d1=end-beg;
        int d2=searchBeg-searchEnd;

        if(d1<d2)
            return end;

        ForwardIterator1 curr1 = beg;
        ForwardIterator2 curr2 = searchBeg;

        while (curr2 != searchEnd)
        {
            if(*curr1 == *curr2)
            {
                ++curr1;
                ++curr2;
            }
            else
            {
                //it means impossible find the subrange
                if(d1 == d2)
                    return end;
                else
                {
                    curr1 = ++beg;
                    curr2 = searchBeg;
                    --d1;
                }

            }
        }

        return beg;
    }
    //search_n
    //search first n matching consecutive elements
    //returns the position of the first of count consecutive elements in the range[beg, end) that all have
    //a value equal the value
    template<typename ForwardIterator, typename Size, typename T>
    ForwardIterator search_n(ForwardIterator beg, ForwardIterator end, Size count, const T& value)
    {
        if(count <= 0)
            return beg;
        //find the first position of value
        while(beg!=end)
        {
            if(*beg == value)
                break;
            else
                ++beg;
        }
        //continue find the last values
        while (beg != end)
        {
            Size n = count - 1;
            ForwardIterator i = beg;
            ++i;
            while(*i == value && n != 0 && i != end)
            {
               ++i;
               --n;
            }
            if(n==0)
                return beg;
            else
            {
                while(i!=end)
                {
                    if(*i == value)
                        break;
                    else
                        ++i;
                }
                beg = i;
            }

        }
        return end;

    }
    //search first or last possible position
    //lower_bound returns the position of the first element that has a value equal to or greater than value
    //upper_bound returns the position of the first element that has a value greater than value
    //this is a random access iterator version(vector etc.)
    template<typename RandomAccessIterator, typename T>
    RandomAccessIterator lower_bound(RandomAccessIterator first, RandomAccessIterator last, T& value)
    {
        int len = last - first;
        int half = 0;

        RandomAccessIterator middle;

        while (len > 0) {
            half = len>>1;
            middle = first + half;
            if(*middle < value)
            {
                first = middle+1;
                len = len - half -1;
            }
            else
            {
                len = half;
            }
        }
        return first;

    }
    template<typename RandomAccessIterator, typename T>
    RandomAccessIterator upper_bound(RandomAccessIterator first, RandomAccessIterator last, T& value)
    {
        int len = last - first;
        int half = 0;

        RandomAccessIterator middle;

        while (len > 0) {
            half = len>>1;
            middle = first + half;
            if(*middle <= value)
            {
                first = middle+1;
                len = len - half -1;
            }
            else
            {
                len = half;
            }
        }
        return first;

    }
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
