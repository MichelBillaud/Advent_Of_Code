      program CrabCups
C
C AOC 2020, Day 23 Crab Cups - part 1 and 2
C written in Fortran 77
C michel billaud   14-15 jan 2022    
C
C ring buffer replaced by a circular chaining
C
      integer small(9), puzzle(9)
      data small  /3, 8, 9, 1, 2, 5, 4, 6, 7/
      data puzzle /3, 6, 2, 9, 8, 1, 7, 5, 4/
      call part1("Small 10", small, 10)
      call part1("Small 100", small, 100)
      call part1("Puzzle 100", puzzle, 100)
      
      call part2("Small", small)
      call part2("Puzzle", puzzle)

      end program CrabCups

C
C Part 1
C
      subroutine part1(name, initial, steps)
      implicit none
      character*(*) name
      integer initial(9)
      integer steps

      integer next(9)
      integer i, current, step

      do i = 1, 8
            next(initial(i)) = initial(i+1)
      end do
      next (initial(9)) = initial(1)

      current = initial(1)
      call display9(0, current, next)
      do step = 1, steps
            call execute_step(current, next, 9)
            call display9(step, current, next)
      end do 
      call display_part1_answer(name, current, next)
      end subroutine part1
C
C auxiliary function for part 1
C
      subroutine display_part1_answer(name, current, next)
      implicit none
      character*(*) name    
      integer current, next(9)
      integer display(8)
      integer i
      display(1) = next(1)
      do i = 2, 8
            display(i) = next(display(i-1))
      end do
      print "('# Part1 ', A, ' : ', 8I1)", name, display
      end subroutine display_part1_answer

      subroutine display9(step, current, next)
      implicit none
      integer step, current, next(9)
      integer display(9), i
      display(1) = current
      do i = 2, 8
            display(i) = next(display(i-1))
      end do
      print "(I3,':',9I3)", step, display
      end subroutine display9

C
C Part 2
C
      subroutine part2(name, initial)
      implicit none
      character*(*) name
      integer initial(9)
      integer MILLION
      parameter (MILLION = 1000000)

      integer next(MILLION)
      integer i, current, step

      do i = 1, 8
            next(initial(i)) = initial(i+1)
      end do
      next(initial(9)) = 10
      do i = 10, MILLION - 1
            next(i) = i+1
      end do
      next(MILLION) = initial(1)
      current = initial(1)
  
      do step = 1, 10 * MILLION
            call execute_step(current, next, MILLION)
      end do
      call display_part2_answer(name,current,next)

      end subroutine part2  

C
C auxiliary for part 2
C
      subroutine display_part2_answer(name, current, next)
      implicit none
      character*(*) name    
      integer current, next(9)
      integer*8 v1, v2, product
      v1 = next(1)
      v2 = next(v1)
      product = v1 * v2
      print *, "Part 2 ", name, product
      end subroutine display_part2_answer


C
C Execute_Step
C
      subroutine execute_step(current, next, size)
      integer current
      integer size
      integer next(size)
      integer followers(3), f, destination
      integer*8 product
      f = current
      do i = 1,3
            f = next(f)
            followers(i) = f
      end do
      destination = current - 1
      if (destination.eq.0) destination = size
      do while ((destination.eq.followers(1))
     S             .or. (destination.eq.followers(2))
     S             .or. (destination.eq.followers(3)))
            destination = destination - 1
            if (destination.eq.0) destination = size
      end do
      
      next(current) = next(followers(3))
      next(followers(3)) = next(destination)
      next(destination) = followers(1)
      current = next(current)

      end subroutine execute_step