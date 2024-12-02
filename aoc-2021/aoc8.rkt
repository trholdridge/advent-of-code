#lang racket

(require 2htdp/batch-io)

; Input

; a Segment is one of:
; - "a"
; - "b"
; - "c"
; - "d"
; - "e"
; - "f"
; - "g"
(define (segment-temp s)
  (cond
    [(string=? "a" s) ...]
    [(string=? "b" s) ...]
    [(string=? "c" s) ...]
    [(string=? "d" s) ...]
    [(string=? "e" s) ...]
    [(string=? "f" s) ...]
    [(string=? "g" s) ...]))

(define-struct entry [signals output])
; an Entry is a (make-struct [List-of [List-of Segment]] [List-of [List-of Segment]])
; represents a data entry

(define RAW-INPUT (read-lines "input8.txt"))

