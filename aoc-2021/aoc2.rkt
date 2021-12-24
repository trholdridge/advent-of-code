;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname aoc2) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)
(require racket/string)


(define-struct sub [x y aim])
(define SUB1 (make-sub 0 0 0))
(define SUB2 (make-sub 0 0 3))

; Movement functions

(check-expect (down SUB1 2) (make-sub 0 0 2))
(check-expect (down SUB2 7) (make-sub 0 0 10))
(define (down s n)
  (make-sub (sub-x s)
            (sub-y s)
            (+ (sub-aim s) n)))

(check-expect (up SUB1 4) (make-sub 0 0 -4))
(check-expect (up SUB2 1) (make-sub 0 0 2))
(define (up s n)
  (make-sub (sub-x s)
            (sub-y s)
            (- (sub-aim s) n)))

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


; ---------------------

; execute-commands : Sub [List-of [Sub -> Sub]] -> Sub
(define (execute-commands s loc)
  (foldl (λ (command sub) (command sub)) s loc))

(define INPUT (read-lines "input2.txt"))
(define COMMANDS (map string->command INPUT))

(define (solve commands)
  (local [(define FINAL-SUB (execute-commands (make-sub 0 0 0) commands))]
    (* (sub-x FINAL-SUB) (sub-y FINAL-SUB))))