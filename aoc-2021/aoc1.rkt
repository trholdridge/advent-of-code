;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname aoc1) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)
(require racket/string)

; Input

(define RAW-INPUT (read-lines "input.txt"))
(define INPUT (map string->number RAW-INPUT))

; --------------- PART 1 ---------------

; number-of-increases : [NEList-of Nat] -> Nat
; returns number of measurements larger than the previous measurement
(check-expect (number-of-increases '(1)) 0)
(check-expect (number-of-increases '(1 2 2 4)) 2)
(check-expect (number-of-increases '(1 3 2 1)) 1)
(define (number-of-increases lon)
  (cond
    [(empty? (rest lon)) 0]
    [(cons? (rest lon)) (+ (if (< (first lon) (first (rest lon)))
                               1
                               0)
                           (number-of-increases (rest lon)))]))

; --------------- PART 2 ---------------

;; number-of-increases/v2 : [NEList-of Nat] -> Nat
; returns # of sliding measurements larger than previous sliding measurement
(check-expect (number-of-increases/v2 '(1 2 3)) 0)
(check-expect (number-of-increases/v2 '(1 2 2 4)) 1)
(check-expect (number-of-increases/v2 '(1 3 2 1)) 0)
(define (number-of-increases/v2 input)
  (local [; measurements->sliding : [NEList-of Nat] -> [NEList-of Nat]
          ; converts list of measurements to list of sliding measurements
          (define (measurements->sliding lon)
            (cond
              [(< (length lon) 3) '()]
              [(>= (length lon) 3) (cons (+ (first lon)
                                            (second lon)
                                            (third lon))
                                         (measurements->sliding (rest lon)))]))]
    (number-of-increases (measurements->sliding input))))
