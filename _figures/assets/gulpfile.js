const gulp = require('gulp');
const sass = require('gulp-sass');
const plumber = require('gulp-plumber');
const notify = require('gulp-notify');

const moduleDir = './node_modules/';

gulp.task('sass', () => {
  return gulp.src('./scss/**/*.scss')
    .pipe(plumber({
      errorHandler: notify.onError("Error: <%= error.message %>")
    }))
    .pipe(sass({
      includePaths: [
        moduleDir + 'ress/',
        moduleDir + '@fortawesome/fontawesome-free/css/'
      ]
    }).on('error', sass.logError))
    // .pipe(autoprefixer({
    //   browsers: ['last 2 versions', 'ie >= 11', 'Android >= 4']
    // }))
    .pipe(gulp.dest('./css'));
});

gulp.task('sass:watch', () => {
  gulp.watch('./scss/**/*.scss', gulp.task('sass'));
});

gulp.task('default', gulp.series(gulp.parallel('sass')));
