      program BinaryBoarding
C
C AOC 2020, Day 5 Binary Boarding, part 1 
C written in Fortran 77
C michel billaud   14 dec 2021
C
      character *20 filename 
      print *, "AOC 2020 Day 5 Binary Boarding - part 1"

      filename = "../small.txt"
      call part1(filename)
      filename = "../large.txt"
      call part1(filename)

      end program

C
C Process a file. Displays the highest seat number
C

      subroutine part1(filename)
      integer extract_int_from_pass

      character*20 filename
      character*10 pass
      character*50 comment
      integer row, col, id
      integer highest_seat

      open (1, file = filename, status = 'old', err = 404 )
      highest_seat = 0
      do while (.true.)
            read (1, "(10A,50A)", end = 100) pass, comment
C           print *, "pass = ", pass, ", comment = ", comment
            row =  extract_int_from_pass(pass, 1, 7,  "B")
            col =  extract_int_from_pass(pass, 8, 10, "R")
            id = 8 * row + col
C           print *, "row =", row, "col =", col, "id = ", id
            if (id.gt.highest_seat) highest_seat = id
      end do
     
100   print *,"Part 1. Highest seat for", filename, "is", highest_seat
      close(1)
      return
404   print *,"file not found" 
      end
    
      integer function extract_int_from_pass(pass, first, last, upper)
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
      end
      