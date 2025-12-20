import cats.effect._
import scala.io.Source

object Day10 extends IOApp {

  private type Button = Int
  final case class Machine(buttons: Set[Button],
                           targetLights: Int,
                           targetJoltages: List[Int])

  def part1(lines: Iterator[String]): Long = {
    val machines = lines.map(parse)
    machines.map { m =>
      val powerset = m.buttons.subsets.toList.sortBy(_.size)
      powerset
        .find { subset =>
          subset.foldLeft(0) {
            _ ^ _
          } == m.targetLights
        }
        .map(_.size)
        .getOrElse(0)
    }.sum
  }

  def part2(lines: Iterator[String]): Long = {
    val machines = lines.map(parse)
    machines.map { m =>
      val lotsaButtons = m.buttons.toList.flatMap(b => List.fill(5)(b))
      (1 to lotsaButtons.size)
        .find { numPresses =>
          lotsaButtons
            .combinations(numPresses)
            .toList
            .exists { subset =>
              subset.foldLeft(List.fill(m.targetJoltages.length)(0)) {
                (joltagesSoFar, button) =>
                  joltagesSoFar
                    .zip(
                      button.toBinaryString.reverse
                        .padTo(m.targetJoltages.length, '0')
                        .reverse
                        .map(_.asDigit))
                    .map(j => j._1 + j._2)
              } == m.targetJoltages
            }
        }
        .getOrElse(throw new IllegalArgumentException("no valid solutions???"))
    }.sum
  }

  def parse(line: String): Machine = {
    val numLights = line.indexOf("]") - line.indexOf("[") - 1
    val shifty = 1 << (numLights - 1)
    Machine(
      line
        .substring(line.indexOf("]") + 1, line.indexOf("{"))
        .split("[()]")
        .toSet
        .collect {
          case s if s.matches("[0-9].*") =>
            s.split(",").toList.map(shifty >> _.toInt).sum
        },
      line
        .substring(line.indexOf("[") + 1, line.indexOf("]"))
        .zipWithIndex
        .toList
        .collect {
          case ('#', index) => shifty >> index
        }
        .sum,
      line
        .substring(line.indexOf("{") + 1, line.indexOf("}"))
        .split(",")
        .map(_.toInt)
        .toList
    )
  }

  override def run(args: List[String]): IO[ExitCode] =
    for {
      result <- IO(Source.fromResource("input10.txt")).bracket(src =>
        IO(part2(src.getLines())))(src => IO(src.close()))
      _ <- IO.println(result)
    } yield ExitCode.Success
}
