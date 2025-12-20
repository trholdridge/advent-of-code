scalaVersion := "3.7.4"

libraryDependencies += "org.typelevel" %% "cats-effect" % "3.6.3" withSources() withJavadoc()
libraryDependencies += "org.typelevel" %% "cats-core" % "2.13.0" withSources() withJavadoc()

scalacOptions ++= Seq(
  "-feature",
  "-deprecation",
  "-unchecked",
)