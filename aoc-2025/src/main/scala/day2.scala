import cats.effect._
import java.io.File
import scala.io.Source

object Day2 extends IOApp {

  def part1(line: String): Long = {
    val ranges = line.split(",").map { s =>
        val ends = s.split("-")
        (ends(0).toLong to ends(1).toLong)
    }

    ranges.flatMap(range => range.filter { i =>
        val s = i.toString
        s.take(s.length / 2) == s.drop(s.length / 2)
    }).sum
  }

  def part2(line: String): Long = {
    val ranges = line.split(",").map { s =>
        val ends = s.split("-")
        (ends(0).toLong to ends(1).toLong)
    }

    ranges.flatMap(range => range.filter { i =>
        val s = i.toString
        s.matches("^([0-9]+)\\1+$")
    }).sum
  }

  override def run(args: List[String]): IO[ExitCode] =
    for {
      result <- IO(Source.fromResource("test.txt")).bracket(src => IO(part2(src.getLines.next)))(src => IO(src.close()))
      _ <- IO.println(result)
    } yield ExitCode.Success
}