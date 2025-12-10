import cats.effect._
import java.io.File
import scala.io.Source

object Day5 extends IOApp {

  def part1(lines: Iterator[String]): Long = {
    val linesCopy = lines.toList
    val rangeLines = linesCopy.filter(_.contains('-'))
    val idLines = linesCopy.filter(line => !line.isEmpty() && !line.contains('-'))

    val ranges = rangeLines.map { range =>
        val ends = range.split("-")
        (ends(0).toLong, ends(1).toLong)
    }
    val ids = idLines.map(_.toLong).toList

    ids.count(id => ranges.exists(ends => id >= ends._1 && id <= ends._2))
  }
  
  def part2(lines: Iterator[String]): Long = {
    val rangeLines = lines.filter(_.contains('-'))

    val ranges = rangeLines.foldLeft[List[(Long, Long)]](List()) { (soFar, range) =>
        val ends = range.split("-")
        val endsTuple = (ends(0).toLong, ends(1).toLong)
        val overlapping = soFar.filter(overlaps(_, endsTuple))
        merge(endsTuple :: overlapping) :: soFar.diff(overlapping)
    }

    ranges.exists { r1 => 
      ranges.exists { r2 =>
        if (r1 != r2 && overlaps(r1, r2))
          println(s"$r1 $r2")
          true
        else
          false
      }
    }

    ranges.map(range => range._2 - range._1 + 1).sum
  }

  def overlaps(range1: (Long, Long), range2: (Long, Long)): Boolean = {
    (range1._1 >= range2._1 && range1._1 <= range2._2)
      || (range1._2 >= range2._1 && range1._2 <= range2._2)
      || (range2._1 >= range1._1 && range2._1 <= range1._2)
      || (range2._2 >= range1._1 && range2._2 <= range1._2)
  }

  def merge(ranges: List[(Long, Long)]): (Long, Long) = {
    (ranges.map(_._1).min, ranges.map(_._2).max)
  }

  override def run(args: List[String]): IO[ExitCode] =
    for {
      result <- IO(Source.fromResource("input5.txt")).bracket(src => IO(part2(src.getLines())))(src => IO(src.close()))
      _ <- IO.println(result)
    } yield ExitCode.Success
}