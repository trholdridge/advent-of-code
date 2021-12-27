;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname aoc2) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)
(require racket/string)

; --------------- PART 1 ---------------

; A Direction is one of
; - "forward"
; - "down"
; - "up"
; and represents a direction the sub can go
(define F "forward")
(define D "down")
(define U "up")
(define (dir-temp d)
  (cond
    [(string=? F d) ...]
    [(string=? D d) ...]
    [(string=? U d) ...]))

(define-struct move [direction magnitude])
; A Move is a (make-move Direction Nat)
; - where direction is the direction the sub should move
; - magnitude is the amount it should move by
; and represents a movement of the sub
(define EX-MOVE-1 (make-move F 2))
(define EX-MOVE-2 (make-move D 5))
(define EX-MOVE-3 (make-move U 1))
(define (move-temp m)
  (... (move-direction m)
       (move-magnitude m)))

; txt->moves : String -> [List-of Move]
(define (txt->moves t)
  (local [; line->move : String -> Move
          (define (line->move l)
            (make-move (first (string-split l))
                       (string->number (second (string-split l)))))]
    (map line->move (read-lines t))))

(define INPUT2 (txt->moves "input2.txt"))

; calculate-movement : [List-of Move] -> Number
; multiply total horizontal movement by total vertical movement
(define (calculate-movement lom)
  (local [(define FORWARD (filter (λ (m) (string=? F (move-direction m))) lom))
          (define DOWN (filter (λ (m) (string=? D (move-direction m))) lom))
          (define UP (filter (λ (m) (string=? U (move-direction m))) lom))
          ; sum-magnitudes : [List-of Move] -> Nat
          (define (sum-magnitudes moves)
            (foldr (λ (m so-far) (+ (move-magnitude m) so-far)) 0 moves))]
    (* (sum-magnitudes FORWARD)
       (- (sum-magnitudes DOWN)
          (sum-magnitudes UP)))))

; --------------- PART 2 ---------------

(define-struct sub [x y aim])
; A Sub is a (make-sub Nat Nat Nat)
; - where x is the hozirontal position
; - y is the depth
; - and aim is the direction the sub is aiming
; and represents a submarine's position and direction
(define SUB1 (make-sub 0 0 0))
(define SUB2 (make-sub 0 0 3))
(define (sub-temp s)
  (... (sub-x s)
       (sub-y s)
       (sub-aim s)))

; Movement functions

; down : Sub -> Sub
; increases a sub's aim by the given # of units
(check-expect (down SUB1 2) (make-sub 0 0 2))
(check-expect (down SUB2 7) (make-sub 0 0 10))
(define (down s n)
  (make-sub (sub-x s)
            (sub-y s)
            (+ (sub-aim s) n)))

; up : Sub -> Sub
; decreases a sub's aim by the given # of units
(check-expect (up SUB1 4) (make-sub 0 0 -4))
(check-expect (up SUB2 1) (make-sub 0 0 2))
(define (up s n)
  (make-sub (sub-x s)
            (sub-y s)
            (- (sub-aim s) n)))

; forward : Sub -> Sub
; increases a sub's horizontal postion and depth based on its aim
(check-expect (forward SUB1 4) (make-sub 4 0 0))
(check-expect (forward SUB2 3) (make-sub 3 9 3))
(define (forward s n)
  (make-sub (+ (sub-x s) n)
            (+ (sub-y s) (* n (sub-aim s)))
            (sub-aim s)))


; string->command : String -> [Sub -> Sub]
; oops check-expects can't compare functions
;(check-expect (string->command "up 0") (λ (s) (up s 0)))
;(check-expect (string->command "down 13") (λ (s) (down s 13)))
;(check-expect (string->command "forward 2") (λ (s) (forward s 2)))
(define (string->command str)
  (local [(define SPLIT (string-split str " "))
          (define UNITS (string->number (second SPLIT)))]
    (cond
      [(string=? "up" (first SPLIT)) (λ (s) (up s UNITS))]
      [(string=? "down" (first SPLIT)) (λ (s) (down s UNITS))]
      [(string=? "forward" (first SPLIT)) (λ (s) (forward s UNITS))])))

; Final steps

(define INPUT (read-lines "input2.txt"))
(define COMMANDS (map string->command INPUT))

; execute-commands : Sub [List-of [Sub -> Sub]] -> Sub
(define (execute-commands s loc)
  (foldl (λ (command sub-so-far) (command sub-so-far)) s loc))

(define (solve commands)
  (local [(define FINAL-SUB (execute-commands (make-sub 0 0 0) commands))]
    (* (sub-x FINAL-SUB) (sub-y FINAL-SUB))))