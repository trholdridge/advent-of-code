import cats.effect._
import java.io.File
import scala.io.Source

object Day6 extends IOApp {

  def part1(lines: Iterator[String]): Long = {
    val rows = lines.toList.map(_.trim.split("\\s+").toList)
    val nums = rows.dropRight(1).map(_.map(_.toLong))
    val fns = rows.takeRight(1)(0)

    val equations = nums.transpose.zip(fns)
    equations.map {
        case (ns, f) =>
            if (f == "+")
                ns.sum
            else
                ns.product
    }.sum
  }

  def part2(lines: Iterator[String]): Long = {
    val linesCopy = lines.toList
    val charGrid = linesCopy.dropRight(1).map(_.toCharArray().toList).transpose
    val fns = linesCopy.takeRight(1)(0).trim.split("\\s+").toList
    val groupedGridPair = charGrid.foldLeft((List(), List())) { (soFar, col) =>
        if (col.forall(_ == ' '))
            (soFar._1 ++ List(soFar._2), List())
        else
            (soFar._1, soFar._2 ++ List(col))
    }
    val groupedGrid = groupedGridPair._1 ++ List(groupedGridPair._2)
    val results = groupedGrid.zip(fns)map { eq =>
        val nums = eq._1.map(_.mkString.trim.toLong)
        if (eq._2 == "+")
            nums.sum
        else
            nums.product
    }
    results.sum
  }

  override def run(args: List[String]): IO[ExitCode] =
    for {
      result <- IO(Source.fromResource("input6.txt")).bracket(src => IO(part2(src.getLines)))(src => IO(src.close()))
      _ <- IO.println(result)
    } yield ExitCode.Success
}