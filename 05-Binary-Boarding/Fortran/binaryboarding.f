      program BinaryBoarding
C
C AOC 2020, Day 5 Binary Boarding, part 1 and 2
C written in Fortran 77
C michel billaud   14 dec 2021
C
      character *20 filename 
      print *, "AOC 2020 Day 5 Binary Boarding - part 1"

      filename = "../small.txt"
      call part1(filename)
      filename = "../large.txt"
      call part1(filename)

      call part2(filename)
      end program
C 
C Refactoring: 
C     Part 2 can be solved by 
C     1. an old trick:
C        if L is a list of distinct numbers,
C        and L' is L deprived from one element, 
C        then the missing number is sum(L) - sum(L').
C     2. the fact that the list of ids is the interval
C        min..max
C     So the previous code of part1 is slightly generalized
C     into the computation of min, max, and sum of ids from
C     the data file.
C Part 1 
C
      subroutine part1(filename)

      implicit none
      character*20 filename
      integer min, max, sum
      call process_file(filename, min, max, sum)
      print *,"Part 1. Highest seat for ", filename, "is", max
  
      end subroutine part1

C
C Part 2 
C     old trick: if L is a list of distinct numbers,
C     and L' is L deprived from one element, 
C     then the missing number is sum(L) - sum(L').
C
      subroutine part2(filename)

      implicit none
      character*20 filename
      integer min, max, sum
      integer missing

      integer sum_of_range

      call process_file(filename, min, max, sum)
      missing = sum_of_range(min, max) - sum
      print *,"Part 2. Missing seat in  ", filename, "is", missing
C      print *, "min =", min, "max =", max, "sum =", sum
      end subroutine part2

C
C Process a file. Computes min, max and sum if ids.
C
      subroutine process_file(filename, min, max, sum)

      implicit none
      character*20 filename
      integer min, max, sum  
      
      character*10 pass
      character*50 comment
      integer row, col, id
   
      integer extract_int_from_pass

      min = 9999
      max = 0
      sum = 0

      open (1, file = filename, status = 'old', err = 404 )
      do while (.true.)
            read (1, "(10A,50A)", end = 100) pass, comment
C           print *, "pass = ", pass, ", comment = ", comment
            row =  extract_int_from_pass(pass, 1, 7,  "B")
            col =  extract_int_from_pass(pass, 8, 10, "R")
            id = 8 * row + col
C           print *, "row =", row, "col =", col, "id = ", id
            sum = sum + id
            if (id.lt.min) min = id
            if (id.gt.max) max = id
      end do
     
100   close(1)
      return

404   print *,"file not found", filename 
      end subroutine process_file
    
C
C     Auxiliary stuff for conversion
C
      integer function extract_int_from_pass(pass, first, last, upper)
      
      implicit none
      character*10 pass
      integer first, last
      character upper
      integer r, i
      
      r = 0
      do i = first, last
            r = 2*r
            if (pass(i:i).eq.upper) r = r + 1
      end do
      extract_int_from_pass = r
      return
      end function extract_int_from_pass

C
C     compute a + (a+1) + (a+2) + ... + b
C
      integer function sum_of_range(a, b)
      integer a, b
      sum_of_range = (a + b)*(b - a +1) /2
      return 
      end function sum_of_range
      