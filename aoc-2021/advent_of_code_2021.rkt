;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname advent_of_code_2021) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)
(require racket/string)

;; ----- Day 1 -----

;(define RAW-INPUT (read-lines "input.txt"))
;(define INPUT (map string->number RAW-INPUT))

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

; ----- Day 2 -----

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