#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>

int main() {

    // Creamos el nodo raíz
    osg::ref_ptr<osg::Group> root = new osg::Group;

    // Creamos los cubo utilizando ShapeDrawable y Box
    osg::ref_ptr<osg::ShapeDrawable> cubeDrawable = new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 1.0f));
    osg::ref_ptr<osg::ShapeDrawable> cubeDrawable2 = new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 0.8f));

    // Creamos los estados para los colores
    osg::ref_ptr<osg::StateSet> stateSet = cubeDrawable->getOrCreateStateSet();
    osg::ref_ptr<osg::StateSet> stateSet2 = cubeDrawable->getOrCreateStateSet();

    // Añadimos los colores a las caras de los cubos
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Rojo
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f)); // Verde
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f)); // Azul
    colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f)); // Amarillo
    colors->push_back(osg::Vec4(1.0f, 0.0f, 1.0f, 1.0f)); // Magenta
    colors->push_back(osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f)); // Cyan
    cubeDrawable->setColorArray(colors);
    cubeDrawable->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    cubeDrawable2->setColorArray(colors);
    cubeDrawable2->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    // Creamos un material para establecer el modo de color
    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
    material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8f, 0.8f, 0.8f, 1.0f));

    // Aplicamos el material a los conjuntos de estado
    stateSet->setAttributeAndModes(material, osg::StateAttribute::ON);
    stateSet2->setAttributeAndModes(material, osg::StateAttribute::ON);

    // Creamos los nodos Geode
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::Geode> geode2 = new osg::Geode;

    // Añadimos las formas de los cubos a los nodos Geode
    geode->addDrawable(cubeDrawable);
    geode2->addDrawable(cubeDrawable2);

    // Creamos nodos Transform para rotar los cubos
    osg::ref_ptr<osg::MatrixTransform> cubeTransform = new osg::MatrixTransform;
    osg::ref_ptr<osg::MatrixTransform> cubeTransform2 = new osg::MatrixTransform;
    cubeTransform->addChild(geode);
    cubeTransform2->addChild(geode2);

    // Creamos un visor para visualizar la escena
    osgViewer::Viewer viewer;

    // Configuramos el tamaño de la ventana
    viewer.setUpViewInWindow(200, 200, 1000, 800);
    // viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    // Añadimos los nodos Transform al nodo raíz y lo usamos como escena
    root->addChild(cubeTransform);
    root->addChild(cubeTransform2);
    viewer.setSceneData(root);

    // Alejamos la cámara
    osg::Matrixd viewMatrix;
    viewMatrix.makeTranslate(0.0, 0.0, -10.0);
    viewer.getCamera()->setViewMatrix(viewMatrix);

    // Configuramos las rotaciones de los cubos
    float angle = 0.0f;
    while (!viewer.done()) {
        osg::Matrix rotationMatrix, rotationMatrix2;
        // Rotación en el eje Y
        rotationMatrix.makeRotate(angle, osg::Vec3(0.0f, 1.0f, 0.0f));
        cubeTransform->setMatrix(rotationMatrix);
        
        // Traslación del segundo cubo antes de rotarlo
        osg::Matrix translateMatrix;
        translateMatrix.makeTranslate(osg::Vec3(2.0f, 0.0f, 0.0f));
        // Aplica rotación en el sistema de coordenadas local
        rotationMatrix2 = rotationMatrix * translateMatrix; 
        cubeTransform2->setMatrix(rotationMatrix2);

        angle += 0.01f;
        viewer.frame();
    }

    return 0;
}
