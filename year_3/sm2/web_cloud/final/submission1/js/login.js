$(document).ready(function () {
    $("form").submit(function (event) {
        event.preventDefault();
        $('#dogModal').modal('show');
    });
});