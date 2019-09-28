from django.db import models


# Create your models here.
class City(models.Model):
    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=10)
    category = models.ForeignKey(to='Category', on_delete=models.CASCADE)
    year = models.ForeignKey(to='Year', on_delete=models.CASCADE)
    keywords = models.TextField(null=True)
    img_url = models.CharField(max_length=100)

    def __str__(self):
        return '%s_%s_%s' % (self.name, self.category, self.year)

    class Meta:
        ordering = ['-year']


class Year(models.Model):
    id = models.AutoField(primary_key=True)
    year = models.CharField(max_length=10)

    def __str__(self):
        return self.year


class Category(models.Model):
    id = models.AutoField(primary_key=True)
    category = models.CharField(max_length=10)

    def __str__(self):
        return self.category
