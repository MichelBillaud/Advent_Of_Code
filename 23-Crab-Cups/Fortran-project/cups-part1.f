      program CrabCups
C
C AOC 2020, Day 23 Crab Cups - part 1
C written in Fortran 77
C michel billaud   14-15 jan 2022    
C
      
      implicit none
      integer small(9), puzzle(9)
      data small  /3, 8, 9, 1, 2, 5, 4, 6, 7/
      data puzzle /3, 6, 2, 9, 8, 1, 7, 5, 4/
      
      integer result(9)
      
      print *, "AOC 2020 Day 23 Crab Cups -- part 1"

      call simulate(small, result, 10)
      print *, "- expected for 10 steps was 92658374"
      call simulate(small, result, 100)
      print *, "- expected for 100 steps was 67384529"
      call simulate(puzzle, result, 100)
      print *, "- puzzle answer for part 1"
      
      print *, "Done"
      end program
C
C
C
      subroutine simulate(initial, current, steps)
      implicit none
      integer initial(9), current(9), steps
      integer next(9), step
      integer i
      integer dest_index
      integer find_dest_index
      integer last
      
      current = initial
      call display("Initial:", current, 0)
      
      do step = 1, steps      
C        call display(current, step-1)         
         dest_index = find_dest_index(current);

         last = 0
         do i = 5, dest_index
            last = last + 1
            next(last) = current(i)
         end do
         do i = 2, 4
            last = last + 1
            next(last) = current(i)
         end do
         do i = dest_index + 1, 9
            last = last + 1
            next(last) = current(i)
         end do
         next(9) = current(1)

         current = next
         
      end do

      print *, "Final:"
      call display("Final:", current, steps)
      call display_result(current, steps)
      end subroutine simulate

      
C
C Find_Dest_Index
C
      integer function find_dest_index(current)
      implicit none
      integer current(9)
      integer value, index

      value = current(1) - 1
      if (value.eq.0) value  = 9
      do while ((value.eq.current(2))
     S     .or. (value.eq.current(3))
     S     .or. (value.eq.current(4)))
         value = value - 1
         if (value.eq.0) value = 9 
      end do

      index = 4
      do while (current(index).ne.value)
         index = index + 1
      end do
      
      find_dest_index = index
      return
      end function find_dest_index


C
C Display
C
      
      subroutine display(message, current, step)
      implicit none
      character*(*) message
      integer current(9), step
      integer start, i

      start = mod(step, 9) + 1
      if (start.eq.1) then
         print 1000, message,
     S        '(',current(1), ')',
     S        (' ', current(i), ' ', i = 2, 9)
      else if (start.eq.9) then
         print 1000, message,
     S        (' ', current(i), ' ', i = 1, 8),
     S        '(',current(9), ')'
      else         
         print 1000 , message,
     S        (' ', current(I),' ', i = 9-start+2, 9),
     S        '(', current(1),')',
     S        (' ', current(I),' ',  i= 2, 9 - start + 1)
      end if
 1000 format (A,9(A1,I1,A1))
      end subroutine display

C     
C Display_Result
C      
      subroutine display_result(current, step)
      implicit none
      integer current(9), step
      integer start, i

      integer display(8)
      start = 1
      do while (current(start).ne.1)
         start = start + 1
      end do

      do i = 1, 8
         start = start + 1
         if (start.eq.10) start = 1
         display(i) = current(start)
      end do
      print 1000 , 'Result: ', display
 1000 format (A,8I1)

      end subroutine display_result
